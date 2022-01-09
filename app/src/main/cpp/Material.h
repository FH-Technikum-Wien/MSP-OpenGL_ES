#pragma once


class Material {
public:
    unsigned int texture = 0;

    Material() = default;
    Material(char* data);

    unsigned int LoadPKMTexture(char* data);
};
