void UpdateMinMaxCoord(const Vertex &v, Vertex &minCoord, Vertex &maxCoord) {
    if (v.x < minCoord.x)
        minCoord.x = v.x;
    if (v.y < minCoord.y)
        minCoord.y = v.y;
    if (v.z < minCoord.z)
        minCoord.z = v.z;

    if (v.x > maxCoord.x)
        maxCoord.x = v.x;
    if (v.y > maxCoord.y)
        maxCoord.y = v.y;
    if (v.z > maxCoord.z)
        maxCoord.z = v.z;
}

bool LoadScaleInfo(const char *filename, ImageScale &scale) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for reading. Using default scale info.\nNote: you can try to use 'make auto-config' or 'make config-scales' if the first didn't solve your problem\n", filename);
        return 0;
    }
    fscanf(input, "%lf %lf %lf", &(scale.x), &(scale.y), &(scale.z));
    return 1;
}
