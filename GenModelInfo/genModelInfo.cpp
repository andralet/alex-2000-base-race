#include "genModelDefines.hpp"

const int MODELINFO_POSTFIX_SIZE = 11; //'.modelinfo\0'
const char MODELINFO_POSTFIX[MODELINFO_POSTFIX_SIZE] = ".modelinfo";
const ModelInfo *DFL_MODELS[OBJ_FILE_NUM] = {&CAR_MODELINFO, &LOW_CAR_MODELINFO, &TREE_MODELINFO, &LOW_TREE_MODELINFO};

int LoadObjPartNumber(const char *filename);
bool SaveModelInfo(const char *objFilename, const int &partNumber, const ModelInfo &modelinfo);
bool GenModelInfo(const char *filename);
bool AutoGenModelInfo(const char *filename, const ModelInfo &modelinfo);

int LoadObjPartNumber(const char *filename) {
    unsigned int vNumber = 0;
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for reading. Cannot get parts number.\n", filename);
        return -1;
    }

    char cmd[MAX_OBJ_CMD_SIZE] = "";
    Vertex readV;
    Triangle readF;
    bool newPart = 0;
    int curPartId = 0;
    while (fscanf(input, "%s", cmd) != EOF) {
        if (strcmp(cmd, "v") == 0) {
            if (newPart) {
                newPart = 0;
                curPartId++;
            }
            fscanf(input, "%lf %lf %lf", &(readV.x), &(readV.y), &(readV.z));
            vNumber++;
        }
        else if (strcmp(cmd, "f") == 0) {
            newPart = 1;
            fscanf(input, "%d %d %d", &(readF.vertex[0]), &(readF.vertex[1]), &(readF.vertex[2]));
            for (int i = 0; i < 3; i++) {
                readF.vertex[i]--;
                if (readF.vertex[i] < 0) {
                    fprintf(stderr, "Error while loading '%s': incorrect file format (too small vertex id). Cannot get parts number.\n", filename);
                    fclose(input);
                    return -1;
                }
                else if ((unsigned int)(readF.vertex[i]) >= vNumber) {
                    fprintf(stderr, "Error while loading '%s': incorrect file format (not enough vertexes). Cannot get parts number.\n", filename);
                    fclose(input);
                    return -1;
                }
            }
        }
    }

    fclose(input);
    curPartId++;
    printf("Successfuly got %d parts from file '%s'.\n", curPartId, filename);

    return curPartId;
}

bool SaveModelInfo(const char *objFilename, const int &partNumber, const ModelInfo &modelinfo) {
    char *dstFile = new char[MAX_FILEPATH];
    if (!ChangeFileNameExtension(objFilename, dstFile, MODELINFO_POSTFIX, MODELINFO_POSTFIX_SIZE)) {
        printf("Cannot generate output filename. Please, specify it manually: ");
        scanf("%s", dstFile);
    }

    FILE *output = fopen(dstFile, "w");
    if (output == NULL) {
        printf("Error: cannot create/clear file '%s'. Model information not saved.\n", dstFile);
        return 0;
    }

    fprintf(output, "%d\n", partNumber);
    for (int i = 0; i < partNumber; i++)
        fprintf(output, "%d %.6f %.6f %.6f\n", modelinfo[i].id, modelinfo[i].color.r, modelinfo[i].color.g, modelinfo[i].color.b);

    fclose(output);
    printf("Model info successfuly saved to '%s'\n", dstFile);
    return 1;
}

bool GenModelInfo(const char *filename) {
    printf("\nLoading '%s'...\n", filename);
    int partNumber = LoadObjPartNumber(filename);
    if (partNumber <= 0) {
        fprintf(stderr, "Cannot get parts number. Model information not generated.\n");
        return 0;
    }

    printf("Note: you should write colors in RGB format: r, g and b from 0.000000 to 1.000000\nAlos you can type -1 -1 -1 to prevent color change.\n");

    ModelInfo modelinfo (partNumber);
    for (int i = 0; i < partNumber; i++) {
        modelinfo[i].id = -1;
        while (modelinfo[i].id < 0 || modelinfo[i].id >= partNumber) {
            printf("Enter part number to draw (from zero): ");
            scanf("%d", &(modelinfo[i].id));
        }
        printf("Enter color in RGB format: ");
        scanf("%f %f %f", &(modelinfo[i].color.r), &(modelinfo[i].color.g), &(modelinfo[i].color.b));
    }

    return SaveModelInfo(filename, partNumber, modelinfo);
}

bool AutoGenModelInfo(const char *filename, const ModelInfo &modelinfo) {
    printf("\nLoading '%s'...\n", filename);
    int partNumber = LoadObjPartNumber(filename);
    if (partNumber <= 0) {
        fprintf(stderr, "Cannot get parts number. Model information not generated.\n");
        return 0;
    }

    if ((unsigned int) partNumber != modelinfo.size()) {
        fprintf(stderr, "Error: part number from '%s' (%d) don't match to default model's (%d). Model information not generated.\n", filename, partNumber, (int) modelinfo.size());
    }

    return SaveModelInfo(filename, partNumber, modelinfo);
}

int main(int argc, const char *argv[]) {
    bool success = 1;

    if (argc != 2 || strcmp(argv[1], "auto") != 0) {
        RunBaseConfigDialog(GenModelInfo, success);
    }
    else {
        for (int i = 0; i < OBJ_FILE_NUM; i++)
            success &= AutoGenModelInfo(OBJ_FILE_LIST[i], *(DFL_MODELS[i]));
    }

    if (success)
        printf("All model info written successfuly.\n");
    else
        printf("There were the errors while writing model info. You should fix them and repeat failed operations.\n");
    return 0;
}
