// Draw/Model/scaleinfo.cpp
    #include "obj.hpp"
    #include "scaleinfo.hpp"

// Draw/Model/modelinfo.cpp
    #include "modelinfo.hpp"
    bool LoadModelinfo(const char *filename, std::vector <PartInfo> &targetModelinfo, int &partNumber);
    void CompileModel(std::vector <PartInfo> &modelinfo, int partLists[], const int targetList);

// Draw/Model/obj.cpp
    void CreateList(int listId, const std::vector <Vertex> &v, const std::vector <Triangle> &f);
    void CopyList(int src, int dst);
    // Just basic .obj format is supported for loading (you can look for examples in Draw/Models)
    // In Blender options are: Apply Modifiers, Objects as OBJ Objects,
    // Scale - 1.0 (generating later with 'make config', I think, is better), Path Mode - Auto, Forward - -Z Forward, Up - Y Up
    bool LoadObj(const char *filename, int partNumber, const int listId[], ImageScale &dfl);
    #include "modelfiles.hpp"

// Draw/Model/model.hpp
    //struct Model;

// Draw/Model/compile.cpp
    const int DRAW_CAR_LIST = 1,
              DRAW_LOW_CAR_LIST = 2,
              DRAW_TREE_LIST = 3,
              DRAW_LOW_TREE_LIST = 4,
              INTERNAL_LIST_START = 1000001;
    void ScaleModel(ImageScale scale);
    int GetNewInternalList(void);
    void CompileDefaultDrawCar(void);
    void CompileDrawObj(ModelFilepath modelFiles, ModelInfo &modelinfo, ImageScale &scale,
                        int drawList, void (*CompileDefaultDrawObj) (void));
    void CompileDrawCar(void);
    void CompileDefaultDrawTree(void);
    void CompileDrawTree(void);
