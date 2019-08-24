const double SMALL_NUM = 1e-10;

const int MAX_FILEPATH = 1024,
          OBJ_FILE_NUM = 4;
const char *OBJ_FILE_LIST[OBJ_FILE_NUM] = {CAR_MODEL_FILES.obj, LOW_CAR_MODEL_FILES.obj,
                                           TREE_MODEL_FILES.obj, LOW_TREE_MODEL_FILES.obj};

bool ChangeFileNameExtension(const char *srcFile, char *dstFile, const char *add, int postfixSize);
void RunBaseConfigDialog(bool (*GenInfo) (const char *), bool &success);
