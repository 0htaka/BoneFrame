#include"MMD\PMXFileReader.h"
#include"MMD\MMDMath.h"
#include"MMD\string_convertor.h"
#include<string>
#include<fstream>
#include"Math\Vector2.h"
#include"Math\Vector3.h"
#include"Math\Matrix.h"
#include"Math\Color.h"

//マテリアル構造体
struct Material {
	Color	ambient;
	Color	diffuse;
	Color	specular;
	Color	emission;
	float	shininess;
	//テクスチャ
	char texture_file_name[128];		//バイナリファイルの保持の仕方に合わせてstringからchar[128]に
	char normal_texture_file_name[128];
	unsigned int texture;	//OpenGLでのテクスチャID
	unsigned int normal_texture;	//OpenGLでのノーマルテクスチャのID
};
//サブセット	どのマテリアルがどこのポリゴンに適応されるかの情報
struct Subset {
	int mat_Index;	//マテリアル番号
	int start;		//インデックスの開始位置
	int count;		//インデックス数
};
struct Vertex {
	Vector3		point;
	Vector3		normal;
	Vector2		texcoord;
	unsigned char	bone_indices[4];
	float			bone_weights[4];
	Vector3		tangent;	//切ベクトル
	Vector3		binormal;	//従法線ベクトル
};

struct Bone {
	char	name[32];
	int		ID;
	int		parentID;
	Matrix	transform;
	Matrix	inverse;
};

void output_simple_mesh(const std::string& simple_mesh_file_name, const mmd::pmx::PMXFile& pmx) {
	std::ofstream file(simple_mesh_file_name, std::ios::binary);
	//マテリアルの出力
	unsigned int material_size = pmx.mesh.materials.size();
	file.write((const char*)&material_size, sizeof(material_size));
	for (const auto& material : pmx.mesh.materials) {
		Material out_material;
		std::memset(&out_material, 0, sizeof(out_material));
		out_material.ambient.r = material.ambient.x;
		out_material.ambient.g = material.ambient.y;
		out_material.ambient.b = material.ambient.z;
		out_material.ambient.a = 1.0f;
		out_material.diffuse.r = material.diffuse.x;
		out_material.diffuse.g = material.diffuse.y;
		out_material.diffuse.b = material.diffuse.z;
		out_material.diffuse.a = 1.0f;
		out_material.specular.r = material.specular.x;
		out_material.specular.g = material.specular.y;
		out_material.specular.b = material.specular.z;
		out_material.specular.a = 1.0f;
		out_material.emission.r = 0.0f;
		out_material.emission.g = 0.0f;
		out_material.emission.b = 0.0f;
		out_material.emission.a = 1.0f;
		out_material.shininess = material.specularity;

		if (material.texture_index != -1) {
			std::string texture_file_name = utf16_to_sjis(pmx.mesh.texture[material.texture_index]);
			strcpy_s(out_material.texture_file_name, texture_file_name.c_str());
			strcpy_s(out_material.normal_texture_file_name, ("normal_" + texture_file_name).c_str());
		}
		file.write((const char*)&out_material, sizeof(out_material));
	}

	//サブセット出力
	unsigned int subset_size = pmx.mesh.materials.size();
	file.write((const char*)&subset_size, sizeof(subset_size));
	int start = 0;
	for (int mat_index = 0; mat_index < (int)pmx.mesh.materials.size(); ++mat_index) {
		Subset subset;
		subset.mat_Index = mat_index;
		subset.start = start;
		subset.count = pmx.mesh.materials[mat_index].vertex_count;
		start += pmx.mesh.materials[mat_index].vertex_count;
		file.write((const char*)&subset, sizeof(subset));
	}
	//頂点インデックの出力
	unsigned int indices_size = pmx.mesh.indices.size();
	file.write((const char*)&indices_size, sizeof(indices_size));
	for (int i = 0; i < (int)pmx.mesh.indices.size(); i += 3) {
		file.write((const char*)&pmx.mesh.indices[i + 0], sizeof(unsigned short));
		file.write((const char*)&pmx.mesh.indices[i + 2], sizeof(unsigned short));
		file.write((const char*)&pmx.mesh.indices[i + 1], sizeof(unsigned short));
	}
	//頂点データの出力
	unsigned int vertices_size = pmx.mesh.vertices.size();
	file.write((const char*)&vertices_size, sizeof(vertices_size));
	for (const auto& vertex : pmx.mesh.vertices) {
		Vertex out_vertex;
		std::memset(&out_vertex, 0, sizeof(out_vertex));
		out_vertex.point.x = vertex.point.x;
		out_vertex.point.y = vertex.point.y;
		out_vertex.point.z = -vertex.point.z;
		out_vertex.normal.x = vertex.normal.x;
		out_vertex.normal.y = vertex.normal.y;
		out_vertex.normal.z = -vertex.normal.z;
		out_vertex.texcoord.x = vertex.uv.x;
		out_vertex.texcoord.y = vertex.uv.y;

		switch (vertex.weight.format)
		{
		case mmd::pmx::BlendWeight::BDEF1:
			out_vertex.bone_indices[0] = (vertex.weight.bdef1.bone != -1) ? vertex.weight.bdef1.bone : 0;
			out_vertex.bone_weights[0] = 1.0f;
			break;
		case mmd::pmx::BlendWeight::BDEF2:
			out_vertex.bone_indices[0] = (vertex.weight.bdef2.bone[0] != -1) ? vertex.weight.bdef2.bone[0] : 0;
			out_vertex.bone_indices[1] = (vertex.weight.bdef2.bone[1] != -1) ? vertex.weight.bdef2.bone[1] : 0;
			out_vertex.bone_weights[0] = vertex.weight.bdef2.weight;
			out_vertex.bone_weights[1] = 1.0f - vertex.weight.bdef2.weight;
			break;
		case mmd::pmx::BlendWeight::BDEF4:
			for (int i = 0; i < 4; ++i) {
				out_vertex.bone_indices[i] = (vertex.weight.bdef4.bone[i] != -1) ? vertex.weight.bdef4.bone[i] : 0;
				out_vertex.bone_weights[i] = vertex.weight.bdef4.weight[i];
			}
			break;
		case mmd::pmx::BlendWeight::SDEF:
			out_vertex.bone_indices[0] = (vertex.weight.sdef.bdef2.bone[0] != -1) ? vertex.weight.sdef.bdef2.bone[0] : 0;
			out_vertex.bone_indices[1] = (vertex.weight.sdef.bdef2.bone[1] != -1) ? vertex.weight.sdef.bdef2.bone[1] : 0;
			out_vertex.bone_weights[0] = vertex.weight.sdef.bdef2.weight;
			out_vertex.bone_weights[1] = 1.0f - vertex.weight.sdef.bdef2.weight;
			break;
		default:
			break;
		}
		out_vertex.tangent.x = vertex.uv_ex[0].x;
		out_vertex.tangent.y = vertex.uv_ex[0].y;
		out_vertex.tangent.z = -vertex.uv_ex[0].z;
		out_vertex.binormal.x = vertex.uv_ex[1].x;
		out_vertex.binormal.y = vertex.uv_ex[1].y;
		out_vertex.binormal.z = -vertex.uv_ex[1].z;
		file.write((const char*)&out_vertex, sizeof(out_vertex));
	}
}

//スケルトンファイルの出力
void output_simple_skeleton(const std::string& simple_mesh_file_name, const mmd::pmx::PMXFile& pmx) {
	std::ofstream file(simple_mesh_file_name, std::ios::binary);
	unsigned int skeleton_size = pmx.skeleton.size();
	file.write((const char*)&skeleton_size, sizeof(skeleton_size));
	for (int id = 0; id < (int)pmx.skeleton.size(); ++id) {
		const auto& bone = pmx.skeleton[id];
		const mmd::float3 parentOffset = (bone.parent_index == -1) ?
			bone.position : (bone.position - pmx.skeleton[bone.parent_index].position);
		Bone out_bone;
		strcpy_s(out_bone.name, utf16_to_sjis(bone.name).c_str());
		out_bone.ID = id;
		out_bone.parentID = bone.parent_index;
		out_bone.transform.Translation(Vector3(parentOffset.x, parentOffset.y, -parentOffset.z));
		out_bone.inverse.Translation(Vector3(-bone.position.x, -bone.position.y, -(-bone.position.z)));
		file.write((const char*)&out_bone, sizeof(out_bone));
	}
}

int main(int argc, const char* argv[]) {
	if (argc < 3) return 1;
	//入力ファイル初期化
	const std::string pmx_file_name = argv[1];
	//出力ファイル名初期化
	const std::string out_mesh_file_name = argv[2];
	const std::string out_skel_file_name = (argc >= 4) ? argv[3] : std::string();
	//Pmxデータ読み込み
	mmd::pmx::PMXFile pmx;
	mmd::pmx::PMXFileReader(pmx).read(pmx_file_name);
	//メッシュファイルの出力
	output_simple_mesh(out_mesh_file_name, pmx);
	//スケルトンファイル出力
	if (!out_skel_file_name.empty()) {
		output_simple_skeleton(out_skel_file_name, pmx);
	}
	return 0;
}