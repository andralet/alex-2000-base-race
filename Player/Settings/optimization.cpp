void LoadOptimization(const char *filename) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Error: cannot open file '%s' for reading. Using default optimization settings.\n", filename);
        return;
    }
    char *option = new char[MAX_OPTION_NAME];
    int i = 0;
    while (fscanf(input, "%s", option) != EOF) {
        for (i = 0; i < OPTION_NUMBER; i++) {
            if (strcmp(option, OPTION_LIST[i].name) == 0) {
                SetOption(input, i);
                break;
            }
        }
        if (i >= OPTION_NUMBER) {
            fprintf(stderr, "Error: unknown option '%s'. Ignoring.\n", option);
            fscanf(input, "%s", option); // to also ignore value of an unknown option
        }
    }

    delete[] option;
    fclose(input);
}

void SetOption(FILE *input, int id) {
    double dataDouble = 0;
    int dataInt = 0;
    switch(OPTION_LIST[id].type) {
        case BOOLEAN:
            fscanf(input, "%d", &dataInt);
            *((bool *)OPTION_LIST[id].data) = (bool)dataInt;
            break;
        case DOUBLE:
            fscanf(input, "%lf", &dataDouble);
            *((double *)OPTION_LIST[id].data) = dataDouble;
            break;
        case INTEGER:
            fscanf(input, "%d", &dataInt);
            *((int *)OPTION_LIST[id].data) = dataInt;
            break;
        default:
            fprintf(stderr, "Internal error in option type recognition. Please, contact the developer.\n");
    }
}
