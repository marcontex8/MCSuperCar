#include "AssimpFactory.h"
#include "Diagnostics.h"
#include <stb_image.h>


extern Diagnostics diagnostics;



void AssimpFactory::setupSimpleCar() {
    diagnostics.log("setupSimpleCar", Diagnostics::Topic::Viewer);

    const aiScene* carScene = loadModel(simpleCarPath);
    if (carScene != nullptr) {
        processNode(carScene->mRootNode, carScene);
    }
}



AssimpFactory::AssimpFactory() {
    setupSimpleCar();
}



AssimpFactory::~AssimpFactory() {

}



SimpleCarDrawer* AssimpFactory::getNewSimpleCarDrawer() {
    return new SimpleCarDrawer(carElements);
}
























const aiScene* AssimpFactory::loadModel(std::string const& path)
{
    diagnostics.log("loadModel Called", Diagnostics::Topic::Viewer);
    // read file via ASSIMP
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        diagnostics.log(std::string("ERROR::ASSIMP:: ") + std::string(importer.GetErrorString()), Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
        return nullptr;
    }
    diagnostics.log("---- Scene name: "    + std::string(scene->mName.C_Str()),      Diagnostics::Topic::Viewer);
    diagnostics.log("     HasAnimations: " + std::to_string(scene->HasAnimations()), Diagnostics::Topic::Viewer);
    diagnostics.log("     HasLights: "     + std::to_string(scene->HasLights()),     Diagnostics::Topic::Viewer);
    diagnostics.log("     HasMaterials: "  + std::to_string(scene->HasMaterials()),  Diagnostics::Topic::Viewer);
    diagnostics.log("     HasMeshes: "     + std::to_string(scene->HasMeshes()),     Diagnostics::Topic::Viewer);
    diagnostics.log("     HasTextures: "   + std::to_string(scene->HasTextures()),   Diagnostics::Topic::Viewer);

    for (int i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];
    }

    return scene;
}

void AssimpFactory::processMaterial(aiMaterial* material, CarElement& element) {
    std::string name = std::string(material->GetName().C_Str());
    diagnostics.log("Material Name: " + name, Diagnostics::Topic::Viewer);

    if (name == "Body") {
        element.texture_diffuse = loadTexture(R"(D:\WorkSpace\MCSuperCar\Modules\world_viewer\graphic\CarPack001\Textures\Hatchback\HatchbackBlue.png)");
        element.texture_specular = loadTexture(R"(D:\WorkSpace\MCSuperCar\Modules\world_viewer\graphic\CarPack001\Textures\Hatchback\Hatchback_Glossiness.png)");

    }
    if (name == "Optics") {
        element.texture_diffuse = loadTexture(R"(D:\WorkSpace\MCSuperCar\Modules\world_viewer\graphic\CarPack001\Textures\Optics.jpg)");
    }
    if (name == "Glass") {

    }
    if (name == "wheel") {
        element.texture_diffuse = loadTexture(R"(D:\WorkSpace\MCSuperCar\Modules\world_viewer\graphic\CarPack001\Textures\Hatchback\wheel_B_Diffuse.png)");
        element.texture_specular = loadTexture(R"(D:\WorkSpace\MCSuperCar\Modules\world_viewer\graphic\CarPack001\Textures\Hatchback\wheel_B_Glossiness.png)");
    }

    for (int i = 0; i < material->mNumProperties; i++) {
        std::string key = material->mProperties[i]->mKey.C_Str();
        diagnostics.log("Material property " + std::to_string(i) + " key: " + key, Diagnostics::Topic::Viewer);
    }
    aiColor3D color(0.f, 0.f, 0.f);
    std::string propertyString;
    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
    propertyString = std::to_string(color.r) + " - " + std::to_string(color.g) + " - " + std::to_string(color.b);
    diagnostics.log("COLOR AMBIENT: " + propertyString, Diagnostics::Topic::Viewer);

    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    propertyString = std::to_string(color.r) + " - " + std::to_string(color.g) + " - " + std::to_string(color.b);
    diagnostics.log("COLOR DIFFUSE: " + propertyString, Diagnostics::Topic::Viewer);

    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
    propertyString = std::to_string(color.r) + " - " + std::to_string(color.g) + " - " + std::to_string(color.b);
    diagnostics.log("COLOR SPECULAR: " + propertyString, Diagnostics::Topic::Viewer);

    material->Get(AI_MATKEY_COLOR_EMISSIVE, color);
    propertyString = std::to_string(color.r) + " - " + std::to_string(color.g) + " - " + std::to_string(color.b);
    diagnostics.log("COLOR EMISSIVE: " + propertyString, Diagnostics::Topic::Viewer);

    material->Get(AI_MATKEY_COLOR_TRANSPARENT, color);
    propertyString = std::to_string(color.r) + " - " + std::to_string(color.g) + " - " + std::to_string(color.b);
    diagnostics.log("COLOR TRANSPARENT: " + propertyString, Diagnostics::Topic::Viewer);

    int shadingModel = 0;

    material->Get(AI_MATKEY_SHADING_MODEL, shadingModel);
    propertyString = std::to_string(shadingModel);
    diagnostics.log("SHADING_MODEL: " + propertyString, Diagnostics::Topic::Viewer);

    float floatProperty = 0.0f;

    material->Get(AI_MATKEY_SHININESS, floatProperty);
    propertyString = std::to_string(floatProperty);
    diagnostics.log("SHININESS: " + propertyString, Diagnostics::Topic::Viewer);

    material->Get(AI_MATKEY_OPACITY, floatProperty);
    propertyString = std::to_string(floatProperty);
    diagnostics.log("OPACITY: " + propertyString, Diagnostics::Topic::Viewer);

    material->Get(AI_MATKEY_REFRACTI, floatProperty);
    propertyString = std::to_string(floatProperty);
    diagnostics.log("REFRACTI: " + propertyString, Diagnostics::Topic::Viewer);
    /*
    std::string textuePath = "";

    for (int i = 0; i < 10; i++) {
        material->Get(_AI_MATKEY_TEXTURE_BASE, aiTextureType_AMBIENT, i, textuePath);
        material->Get(_AI_MATKEY_TEXTURE_BASE, aiTextureType_DIFFUSE, i, textuePath);
        material->Get(_AI_MATKEY_TEXTURE_BASE, aiTextureType_SPECULAR, i, textuePath);


        material->Get(AI_MATKEY_TEXTURE_AMBIENT(i), textuePath);
        diagnostics.log("TEXTUER_AMBIENT " + std::to_string(i) + ": " + textuePath, Diagnostics::Topic::Viewer);

        material->Get(AI_MATKEY_TEXTURE_DIFFUSE(i), textuePath);
        diagnostics.log("TEXTUER_DIFFUSE " + std::to_string(i) + ": " + textuePath, Diagnostics::Topic::Viewer);

        material->Get(AI_MATKEY_TEXTURE_SPECULAR(i), textuePath);
        diagnostics.log("TEXTUER_SPECULAR " + std::to_string(i) + ": " + textuePath, Diagnostics::Topic::Viewer);
    }
    */
    
    aiColor3D colorValue(0.f, 0.f, 0.f);
    float opecityValue = 0.0f;
    material->Get(AI_MATKEY_COLOR_AMBIENT, colorValue);
    element.light_ambient = glm::vec3(colorValue.r, colorValue.g, colorValue.b);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, colorValue);
    element.light_diffuse = glm::vec3(colorValue.r, colorValue.g, colorValue.b);
    material->Get(AI_MATKEY_COLOR_SPECULAR, colorValue);
    element.light_specular = glm::vec3(colorValue.r, colorValue.g, colorValue.b);
    
    float floatValue;
    material->Get(AI_MATKEY_OPACITY, floatValue);
    diagnostics.log("AI_MATKEY_OPACITY: " + std::to_string(floatValue), Diagnostics::Topic::Viewer);
    element.mat_opacity = floatValue;

    material->Get(AI_MATKEY_SHININESS, floatValue);
    diagnostics.log("AI_MATKEY_SHININESS: " + std::to_string(floatValue), Diagnostics::Topic::Viewer);
    element.mat_shininess = floatValue;



}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void AssimpFactory::processNode(aiNode* node, const aiScene* scene)
{
    diagnostics.log("processNode Called", Diagnostics::Topic::Viewer);
    std::string nodeName = node->mName.C_Str();
    diagnostics.log("node->mName: "+ nodeName, Diagnostics::Topic::Viewer);

    diagnostics.log("node->mNumMeshes: "+std::to_string(node->mNumMeshes), Diagnostics::Topic::Viewer);
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        CarElement carElement;
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene, carElement);
        carElement.shaderProgram = shaders.getTextureCarShader();
        glUseProgram(carElement.shaderProgram);

        carElement.modelLocation = glGetUniformLocation(carElement.shaderProgram, "model");
        carElement.viewLocation = glGetUniformLocation(carElement.shaderProgram, "view");
        carElement.projectionLocation = glGetUniformLocation(carElement.shaderProgram, "projection");
        
        carElement.mat_diffuseLocation = glGetUniformLocation(carElement.shaderProgram, "material.diffuse");
        carElement.mat_specularLocation = glGetUniformLocation(carElement.shaderProgram, "material.specular");
        carElement.mat_shininessLocation = glGetUniformLocation(carElement.shaderProgram, "material.shininess");
        carElement.mat_opacityLocation = glGetUniformLocation(carElement.shaderProgram, "material.opacity");
        
        carElement.light_positionLocation = glGetUniformLocation(carElement.shaderProgram, "light.position");
        carElement.light_ambientLocation = glGetUniformLocation(carElement.shaderProgram, "light.ambient");
        carElement.light_diffuseLocation = glGetUniformLocation(carElement.shaderProgram, "light.diffuse");
        carElement.light_specularLocation = glGetUniformLocation(carElement.shaderProgram, "light.specular");
        carElement.viewPosLocation = glGetUniformLocation(carElement.shaderProgram, "viewPos");

        glUniform1i(glGetUniformLocation(carElement.shaderProgram, "material.diffuse"), 0);
        glUniform1i(glGetUniformLocation(carElement.shaderProgram, "material.specular"), 1);

        carElements.push_back(carElement);
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}


CarElement AssimpFactory::processMesh(aiMesh* mesh, const aiScene* scene, CarElement& element)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    //std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

       
    processMaterial(scene->mMaterials[mesh->mMaterialIndex], element);

    std::string numColorChannels = std::to_string(mesh->GetNumColorChannels());
    std::string numUVChannels = std::to_string(mesh->GetNumUVChannels());
    diagnostics.log("numColorChannels = " + numColorChannels, Diagnostics::Topic::Viewer);
    diagnostics.log("numUVChannels = " + numUVChannels, Diagnostics::Topic::Viewer);
    diagnostics.log("HasBones = " + std::string(std::to_string(mesh->HasBones())), Diagnostics::Topic::Viewer);
    diagnostics.log("HasFaces = " + std::string(std::to_string(mesh->HasFaces())), Diagnostics::Topic::Viewer);
    diagnostics.log("HasNormals = " + std::string(std::to_string(mesh->HasNormals())), Diagnostics::Topic::Viewer);
    diagnostics.log("HasPositions = " + std::string(std::to_string(mesh->HasPositions())), Diagnostics::Topic::Viewer);
    diagnostics.log("HasTangentsAndBitangents = " + std::string(std::to_string(mesh->HasTangentsAndBitangents())), Diagnostics::Topic::Viewer);
    
    //mesh->HasTextureCoords();
    //mesh->HasVertexColors();
    
    

    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN
    /*
    // 1. diffuse maps
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    */
    // return a mesh object created from the extracted mesh data
    

    unsigned int VAO, VBO, EBO;
    
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    /*
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    */
    glBindVertexArray(0);

    element.VAO = VAO;
    element.indicesNumber = indices.size();
    return element;
}


unsigned int AssimpFactory::loadTexture(std::string const& path) {
    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load(
        path.c_str(),
        &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



        stbi_image_free(data);
        return texture;
    }
    else
    {
        diagnostics.log("Failed to load texture " + path, Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
        stbi_image_free(data);
        return 0;
    }
}