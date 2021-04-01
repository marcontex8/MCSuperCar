#include "Factory_CarPack001.h"

#include <exception>

#include "Diagnostics.h"
#include <stb_image.h>

constexpr bool SPECIAL_DEBUG_LOGS = false;

extern Diagnostics diagnostics;

CarPack001Factory::CarPack001Factory(Shaders* shaders):shaders(shaders) {
}

CarPack001Factory::~CarPack001Factory() {

}

void CarPack001Factory::setupSimpleCar(carPack001::Model model, carPack001::Color color) {
    diagnostics.log("setting up SimpleCar", Diagnostics::Topic::Viewer);
    currentPaths = getPaths(model, color);
    const aiScene* carScene = loadModel(currentPaths.model);
    if (carScene == nullptr) {
        throw carPack001::LoadingElementException();
    }
    processNode(carScene->mRootNode, carScene);
    customizations.insert(std::pair(std::tuple(model, color), carElements));
    carElements.clear();
}


CarPack001Drawer* CarPack001Factory::getNewSimpleCarDrawer(carPack001::Model model, carPack001::Color color) {
    auto customization = customizations.find(std::tuple(model, color));
    if (customization == customizations.end())
    {
        setupSimpleCar(model, color);
    }
    return new CarPack001Drawer(customizations[std::tuple(model, color)]);
}


const aiScene* CarPack001Factory::loadModel(std::string const& path)
{
    diagnostics.log("loading ASSIMP model: "+path, Diagnostics::Topic::Viewer);
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        diagnostics.log(std::string("ERROR::ASSIMP:: ") + std::string(importer.GetErrorString()), Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
        return nullptr;
    }
    return scene;
}

void CarPack001Factory::processMaterial(aiMaterial* material, CarElement& element) {
    std::string name = std::string(material->GetName().C_Str());
    diagnostics.log("processing material: " + name, Diagnostics::Topic::Viewer);

    if (name == "Body") {
        element.texture_diffuse  =  loadTexture(currentPaths.bodyDiffuseTexture);
        element.texture_specular =  loadTexture(currentPaths.bodyGlossinTexture);
    }
    if (name == "Optics") {
        element.texture_diffuse  =  loadTexture(currentPaths.opticsTexture);
    }
    if (name == "Wheel") {
        element.texture_diffuse  =  loadTexture(currentPaths.wheelDiffuseTexture);
        element.texture_specular =  loadTexture(currentPaths.wheelGlossinTexture);
    }

    aiColor3D colorValue(0.f, 0.f, 0.f);
    material->Get(AI_MATKEY_COLOR_AMBIENT, colorValue);
    element.light_ambient = glm::vec3(colorValue.r, colorValue.g, colorValue.b);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, colorValue);
    element.light_diffuse = glm::vec3(colorValue.r, colorValue.g, colorValue.b);
    material->Get(AI_MATKEY_COLOR_SPECULAR, colorValue);
    element.light_specular = glm::vec3(colorValue.r, colorValue.g, colorValue.b);

    float floatValue;
    material->Get(AI_MATKEY_OPACITY, floatValue);
    //diagnostics.log("AI_MATKEY_OPACITY: " + std::to_string(floatValue), Diagnostics::Topic::Viewer);
    element.mat_opacity = floatValue;
    material->Get(AI_MATKEY_SHININESS, floatValue);
    //diagnostics.log("AI_MATKEY_SHININESS: " + std::to_string(floatValue), Diagnostics::Topic::Viewer);
    element.mat_shininess = floatValue;


    if (SPECIAL_DEBUG_LOGS == true) {
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
    }
}

void CarPack001Factory::processNode(aiNode* node, const aiScene* scene)
{
    std::string nodeName = node->mName.C_Str();
    diagnostics.log("processing node: " + nodeName, Diagnostics::Topic::Viewer);
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        diagnostics.log("creating new car element", Diagnostics::Topic::Viewer);
        CarElement carElement;
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene, carElement);

        carElement.shaderProgram = shaders->getTextureCarShader();
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

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

CarElement CarPack001Factory::processMesh(aiMesh* mesh, const aiScene* scene, CarElement& element)
{
    diagnostics.log("processing mesh", Diagnostics::Topic::Viewer);
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex{ {0,0,0}, {0,0,0}, {0,0} };
        glm::vec3 vector{0, 0, 0};

        // positions
        if (mesh->HasPositions()) {
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
        }
        // normals
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

       
    processMaterial(scene->mMaterials[mesh->mMaterialIndex], element);

    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    element.VAO = VAO;
    element.indicesNumber = indices.size();
    return element;
}


unsigned int CarPack001Factory::loadTexture(std::string const& path) {
    diagnostics.log("loading texture: "+path, Diagnostics::Topic::Viewer);
    unsigned int texture;
    glGenTextures(1, &texture);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
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