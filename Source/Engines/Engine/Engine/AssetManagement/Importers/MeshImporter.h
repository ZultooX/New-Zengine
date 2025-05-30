#pragma once

namespace TGA::FBX { struct Mesh; }

class Mesh;
class MeshImporter
{
public:
	static void Load(const size_t& aID, Mesh& aOutAsset);
	static void Load(const char* aPath, Mesh& aOutAsset);
	static void Unload(Mesh& aOutAsset);

private:
	static void Load_FBX(const char* aPath, Mesh& aOutAsset);
	static void Load_OBJ(const char* aPath, Mesh& aOutAsset);

private:
	static void ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, Mesh& aOutMesh);
};

