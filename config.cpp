bool ChangeFileNameExtension(const char *srcFile, char *dstFile, const char *add, int postfixSize) {
    int i = 0;
    while (i < MAX_FILEPATH && srcFile[i] != '.' && srcFile[i] != '\0') {
        dstFile[i] = srcFile[i];
        i++;
    }
    if (i > MAX_FILEPATH - postfixSize)
        return 0;
    // else
    sprintf(&(dstFile[i]), "%s", add);
    return 1;
}

void RunBaseConfigDialog(bool (*GenInfo) (const char *), bool &success) {
    char *cmd = new char[MAX_FILEPATH];
    cmd[0] = '\0';
    while (strcmp(cmd, "exit") != 0) {
        printf("Specify .obj file path ('Draw/Models/<filename>')\nOr type 'all' to scale all known\nWhen everything is done type 'exit' to exit: ");
        scanf("%s", cmd);
        if (strcmp(cmd, "all") == 0) {
            for (int i = 0; i < OBJ_FILE_NUM; i++)
                success &= GenInfo(OBJ_FILE_LIST[i]);
        }
        else if (strcmp(cmd, "exit") == 0)
            break;
        else
            success &= GenInfo(cmd);
    }
    delete[] cmd;
}
