#include <stdio.h>
#include "defines.hpp"

const int MAX_FILEPATH = 1024,
          SCALEINFO_POSTFIX_SIZE = 11, //'.scaleinfo\0'
          OBJ_FILE_NUM = 2;
const double SMALL_NUM = 1e-10;
const char *OBJ_FILE_LIST[OBJ_FILE_NUM] = {CAR_OBJ_FILEPATH, TREE_OBJ_FILEPATH};

bool LoadObjSize(const char *filename, ImageScale &size);
bool GenScaleFileName(const char *objFile, char *dstFile);
bool GenScaleInfo(const char *filename);
bool AutoGenScaleInfo(const char *filename, ImageScale sizes);

bool LoadObjSize(const char *filename, ImageScale &size) {
    std::vector <Vertex> v;
    v.clear();
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for reading. Cannot get default sizes.\n", filename);
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
                newPart = 0;
                curPartId++;
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
                    fprintf(stderr, "Error while loading '%s': incorrect file format (too small vertex id). Cannot get default sizes.\n", filename);
                    fclose(input);
                    return 0;
                }
                else if ((unsigned int)(readF.vertex[i]) >= v.size()) {
                    fprintf(stderr, "Error while loading '%s': incorrect file format (not enough vertexes). Cannot get default sizes.\n", filename);
                    fclose(input);
                    return 0;
                }
            }
        }
    }

    fclose(input);
    curPartId++;
    printf("Successfuly got default sizes and %d parts from file '%s'.\n", curPartId, filename);

    size.x = maxCoord.x - minCoord.x;
    size.y = maxCoord.y - minCoord.y;
    size.z = maxCoord.z - minCoord.z;
    return 1;
}

bool GenScaleFileName(const char *objFile, char *dstFile) {
    int i = 0;
    while (i < MAX_FILEPATH && objFile[i] != '.' && objFile[i] != '\0') {
        dstFile[i] = objFile[i];
        i++;
    }
    if (i > MAX_FILEPATH - SCALEINFO_POSTFIX_SIZE)
        return 0;
    // else
    sprintf(&(dstFile[i]), ".scaleinfo");
    return 1;
}

bool GenScaleInfo(const char *filename) {
    ImageScale dflSize = {1.0, 1.0, 1.0};
    printf("\nLoading '%s'...\n", filename);
    LoadObjSize(filename, dflSize);

    ImageScale scale = {BASE_WINDOW_WIDTH / dflSize.x, BASE_WINDOW_HEIGHT / dflSize.y, BASE_WINDOW_WIDTH / dflSize.z};
    double baseSize = 0, targetSize = 0;

    printf("Note: onscreen sizes could be found in 'defines.hpp'. In (x, y, z) format:\n");
    printf("Car : (%.1lf, %.1lf, %.1lf)\n", CAR_WIDTH, CAR_HEIGHT, double(CAR_DEPTH) / ROAD_DEPTH * DRAW_ROAD_DEPTH);
    printf("Tree: (%.1lf, %.1lf, %.1lf)\n", TREE_OBJ_X, TREE_OBJ_Y, TREE_OBJ_Z);

    printf("Specify characteristic size for X axis or '0' for default (%lf): ", dflSize.x);
    scanf("%lf", &baseSize);
    if (baseSize < SMALL_NUM)
        baseSize = dflSize.x;
    do {
        printf("Specify onscreen size for X axis (in default window): ");
        scanf("%lf", &targetSize);
    } while (targetSize < SMALL_NUM);
    scale.x = targetSize / baseSize;

    printf("Specify characteristic size for Y axis or '0' for default (%lf): ", dflSize.y);
    scanf("%lf", &baseSize);
    if (baseSize < SMALL_NUM)
        baseSize = dflSize.y;
    do {
        printf("Specify onscreen size for Y axis (in default window): ");
        scanf("%lf", &targetSize);
    } while (targetSize < SMALL_NUM);
    scale.y = targetSize / baseSize;

    printf("Specify characteristic size for Z axis or '0' for default (%lf): ", dflSize.z);
    scanf("%lf", &baseSize);
    if (baseSize < SMALL_NUM)
        baseSize = dflSize.z;
    do {
        printf("Specify onscreen size for Z axis (in default window): ");
        scanf("%lf", &targetSize);
    } while (targetSize < SMALL_NUM);
    scale.z = targetSize / baseSize;

    char *dstFile = new char[MAX_FILEPATH];
    if (!GenScaleFileName(filename, dstFile)) {
        printf("Cannot generate output filename. Please, specify it manually: ");
        scanf("%s", dstFile);
    }

    FILE *output = fopen(dstFile, "w");
    if (output == NULL) {
        printf("Error: cannot create/clear file '%s'. Scale information not saved.\n", dstFile);
        return 0;
    }
    fprintf(output, "%lf %lf %lf", scale.x, scale.y, scale.z);
    fclose(output);
    printf("Scale info successfuly saved to '%s'\n", dstFile);
    return 1;
}

bool AutoGenScaleInfo(const char *filename, ImageScale sizes) {
    ImageScale dflSize = {1.0, 1.0, 1.0};
    printf("\nLoading '%s'...\n", filename);
    LoadObjSize(filename, dflSize);

    ImageScale scale = {sizes.x / dflSize.x, sizes.y / dflSize.y, sizes.z / dflSize.z};
    printf("Scale set to (x, y, z): %.1lf, %.1lf, %.1lf\nSaving...\n", scale.x, scale.y, scale.z);

    char *dstFile = new char[MAX_FILEPATH];
    if (!GenScaleFileName(filename, dstFile)) {
        printf("Cannot generate output filename. Please, specify it manually: ");
        scanf("%s", dstFile);
    }

    FILE *output = fopen(dstFile, "w");
    if (output == NULL) {
        printf("Error: cannot create/clear file '%s'. Scale information not saved.\n", dstFile);
        return 0;
    }
    fprintf(output, "%lf %lf %lf", scale.x, scale.y, scale.z);
    fclose(output);
    printf("Scale info successfuly saved to '%s'\n", dstFile);
    return 1;
}

int main(int argc, char *argv[]) {
    bool success = 1;
    char *cmd = new char[MAX_FILEPATH];
    cmd[0] = '\0';
    if (argc != 2 || strcmp(argv[1], "auto") != 0) {
        while (strcmp(cmd, "exit") != 0) {
            printf("Specify .obj file path ('Draw/Models/<filename>')\nOr type 'all' to scale all known\nWhen everything is done type 'exit' to exit: ");
            scanf("%s", cmd);
            if (strcmp(cmd, "all") == 0) {
                for (int i = 0; i < OBJ_FILE_NUM; i++)
                    success &= GenScaleInfo(OBJ_FILE_LIST[i]);
            }
            else if (strcmp(cmd, "exit") == 0)
                break;
            else
                success &= GenScaleInfo(cmd);
        }
    }
    else {
        ImageScale sizes;
        // car
        sizes.x = CAR_WIDTH; sizes.y = CAR_HEIGHT; sizes.z = double(CAR_DEPTH) / ROAD_DEPTH * DRAW_ROAD_DEPTH;
        success &= AutoGenScaleInfo(CAR_OBJ_FILEPATH, sizes);
        // tree
        sizes.x = TREE_OBJ_X; sizes.y = TREE_OBJ_Y; sizes.z = TREE_OBJ_Z;
        success &= AutoGenScaleInfo(TREE_OBJ_FILEPATH, sizes);
    }

    delete[] cmd;

    if (success)
        printf("All scale info written successfuly.\n");
    else
        printf("There were the errors while writing scale info. You should fix them and repeat failed operations.\n");
    return 0;
}
