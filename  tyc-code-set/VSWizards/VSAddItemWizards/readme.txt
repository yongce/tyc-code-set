本向导属于AddItem类别的扩展。通过此向导，可以向Project中添加模板化了的C++源文件（.h & .cpp文件）。

本向导在VS2008上开发，有两个版本：一个是针对VS2008 Express版，另一个是针对VS2008其它版本。对于.net架构的其它VS版本，应该可以直接使用或者作少量修改即可使用，请自行琢磨。

向导安装方法：
1. 如果是VS2008 Express版本，那么拷贝VS2008_Express目录下的所有子目录到“<VS root>\VC”目录下即可；
2. 如果是其它VS 2008版本，那么拷贝VS2008目录下的所有子目录到“<VS root>\VC”目录下即可。

向导安装完毕后，在Project的弹出对话框“Add New Item / 添加新项”中，可以看到左侧多了一项“My Project Items”，其下有三项“My Header File (*.h)”、“My C++ File (*.cpp)”和“My Class Files (*.h & *.cpp)”，分别用于添加头文件、源文件和类文件。

模板文件修改方法：
1. 模板文件“<VS root>\VC\VCWizards\MyWizards\MyHeaderFile\Templates\1033\headerFile.h”，对应于向导中的“My Header File (*.h)”；
2. 模板文件“<VS root>\VC\VCWizards\MyWizards\MySourceFile\Templates\1033\sourceFile.cpp”，对应于向导中的“My C++ File (*.cpp)”。
3. 模板文件“<VS root>\VC\VCWizards\MyWizards\MyClassFiles\Templates\1033\<headerFile.h & sourceFile.cpp>”，对应于向导中的“My Class Files (*.h & *.cpp)”。

注意：可以（也应该）修改这些模板文件内容来实现自己的需求，但决不能更改这些文件的名字（即headerFile.h和sourceFile.cpp，这两个名字不能改变），否则向导将无法使用。
