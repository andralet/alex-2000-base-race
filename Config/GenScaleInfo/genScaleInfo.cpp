#include "genScaleDefines.hpp"

const int SCALEINFO_POSTFIX_SIZE = 11; //'.scaleinfo\0'
const char SCALEINFO_POSTFIX[SCALEINFO_POSTFIX_SIZE] = ".scaleinfo";
const ImageScale OBJ_SIZES[OBJ_FILE_NUM] = {
    {CAR_WIDTH, CAR_HEIGHT, double(CAR_DEPTH) / ROAD_DEPTH * DRAW_ROAD_DEPTH},
    {CAR_WIDTH, CAR_HEIGHT, double(CAR_DEPTH) / ROAD_DEPTH * DRAW_ROAD_DEPTH},
    {TREE_OBJ_X, TREE_OBJ_Y, TREE_OBJ_Z},
    {TREE_OBJ_X, TREE_OBJ_Y, TREE_OBJ_Z}
};

bool LoadObjSize(const char *filename, ImageScale &size);
bool SaveScaleInfo(const char *objFilename, const ImageScale &scale);
bool GenScaleInfo(const char *filename);
bool AutoGenScaleInfo(const char *filename, const ImageScale &sizes);

bool LoadObjSize(const char *filename, ImageScale &size) {
    unsigned int vNumber = 0;
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
            vNumber++;
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
                else if ((unsigned int)(readF.vertex[i]) >= vNumber) {
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

bool SaveScaleInfo(const char *objFilename, const ImageScale &scale) {
    char *dstFile = new char[MAX_FILEPATH];
    if (!ChangeFileNameExtension(objFilename, dstFile, SCALEINFO_POSTFIX, SCALEINFO_POSTFIX_SIZE)) {
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

    return SaveScaleInfo(filename, scale);
}

bool AutoGenScaleInfo(const char *filename, const ImageScale &sizes) {
    ImageScale dflSize = {1.0, 1.0, 1.0};
    printf("\nLoading '%s'...\n", filename);
    LoadObjSize(filename, dflSize);

    ImageScale scale = {sizes.x / dflSize.x, sizes.y / dflSize.y, sizes.z / dflSize.z};
    printf("Scale set to (x, y, z): %.1lf, %.1lf, %.1lf\nSaving...\n", scale.x, scale.y, scale.z);

    return SaveScaleInfo(filename, scale);
}

int main(int argc, char *argv[]) {
    bool success = 1;

    if (argc != 2 || strcmp(argv[1], "auto") != 0) {
        RunBaseConfigDialog(GenScaleInfo, success);
    }
    else {
        for (int i = 0; i < OBJ_FILE_NUM; i++)
            success &= AutoGenScaleInfo(OBJ_FILE_LIST[i], OBJ_SIZES[i]);
    }

    if (success)
        printf("All scale info written successfuly.\n");
    else
        printf("There were the errors while writing scale info. You should fix them and repeat failed operations.\n");
    return 0;
}
