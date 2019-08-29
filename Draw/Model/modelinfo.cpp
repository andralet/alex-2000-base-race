bool LoadModelinfo(const char *filename, std::vector <PartInfo> &targetModelinfo, int &partNumber) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for reading. Using default model info.\nNote: you can try to use 'make auto-config' or 'make config-models' if the first didn't help\n", filename);
        return 0;
    }

    partNumber = 0;
    targetModelinfo.clear();
    fscanf(input, "%d", &partNumber);

    int id = 0;
    Color color = BLACK;
    for (int i = 0; i < partNumber; i++) {
        fscanf(input, "%d %f %f %f", &id, &(color.r), &(color.g), &(color.b));
        if (id >= partNumber || id < 0) {
            fprintf(stderr, "Error in model loading: irregular part number %d (of %d parts). Model loading aborted.\n", id, partNumber);
            fclose(input);
            return 0;
        }
        targetModelinfo.push_back({id, {color.r, color.g, color.b}});
    }

    fclose(input);
    return 1;
}

void CompileModel(std::vector <PartInfo> &modelinfo, int partLists[], const int targetList) {
    glNewList(targetList, GL_COMPILE); {
        for (unsigned int i = 0; i < modelinfo.size(); i++) {
            SetColor(modelinfo[i].color);
            glCallList(partLists[modelinfo[i].id]);
        }
    } glEndList();
}
