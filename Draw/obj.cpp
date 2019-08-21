void CreateList(int listId, const std::vector <Vertex> &v, const std::vector <Triangle> &f) {
    glNewList(listId, GL_COMPILE); {
        glBegin(GL_TRIANGLES);
        for (unsigned int i = 0; i < f.size(); i++)
            for (int j = 0; j < 3; j++) {
                glVertex3f(v[f[i].vertex[j]].x, v[f[i].vertex[j]].y, v[f[i].vertex[j]].z);
            }
        glEnd();
    } glEndList();
}

void CopyList(int src, int dst) {
    glNewList(dst, GL_COMPILE); {
        glCallList(src);
    } glEndList();
}

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

bool LoadObj(const char *filename, int partNumber, const int listId[], ImageScale &dfl) {
    std::vector <Vertex> v;
    std::vector <Triangle> f;
    v.clear(); f.clear();
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for reading. Using default model.\n", filename);
        return 0;
    }

    char cmd[MAX_OBJ_CMD_SIZE] = "";
    Vertex readV;
    Triangle readF;
    bool newPart = 0;
    int curPartId = 0;
    Vertex minCoord = {INF_COORD, INF_COORD, INF_COORD}, maxCoord = {-INF_COORD, -INF_COORD, -INF_COORD};
    while (fscanf(input, "%s", cmd) != EOF) {
        if (strcmp(cmd, "v") == 0) {
            if (newPart) {
                if (curPartId < partNumber - 1) {
                    CreateList(listId[curPartId], v, f);
                    newPart = 0;
                    f.clear();
                    curPartId++;
                }
                else
                    fprintf(stderr, "Error while loading '%s': too many parts. Writing excess parts to the last list id.\n", filename);
            }
            fscanf(input, "%lf %lf %lf", &(readV.x), &(readV.y), &(readV.z));
            UpdateMinMaxCoord(readV, minCoord, maxCoord);
            v.push_back(readV);
        }
        else if (strcmp(cmd, "f") == 0) {
            newPart = 1;
            fscanf(input, "%d %d %d", &(readF.vertex[0]), &(readF.vertex[1]), &(readF.vertex[2]));
            for (int i = 0; i < 3; i++) {
                readF.vertex[i]--;
                if (readF.vertex[i] < 0) {
                    fprintf(stderr, "Error while loading '%s': incorrect file format (too small vertex id). Using default model.\n", filename);
                    fclose(input);
                    return 0;
                }
                else if ((unsigned int)(readF.vertex[i]) >= v.size()) {
                    fprintf(stderr, "Error while loading '%s': incorrect file format (not enough vertexes). Using default model.\n", filename);
                    fclose(input);
                    return 0;
                }
            }
            f.push_back(readF);
        }
    }

    fclose(input);
    CreateList(listId[curPartId], v, f);
    curPartId++;
    if (curPartId < partNumber) {
        fprintf(stderr, "Error while loading '%s': not enough parts. Filling excess list ids with last part.\n", filename);
        int lastList = curPartId - 1;
        while (curPartId < partNumber) {
            CopyList(listId[lastList], listId[curPartId]);
            partNumber++;
        }
    }

    dfl.x = DFL_WIDTH / (maxCoord.x - minCoord.x);
    dfl.y = DFL_HEIGHT / (maxCoord.y - minCoord.y);
    dfl.z = DFL_DEPTH / (maxCoord.z - minCoord.z);
    return 1;
}

bool LoadScaleInfo(const char *filename, ImageScale &scale) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for reading. Using default scale info.\nNote: you can try to use 'make config'", filename);
        return 0;
    }
    fscanf(input, "%lf %lf %lf", &(scale.x), &(scale.y), &(scale.z));
    return 1;
}
