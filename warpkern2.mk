##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=warpkern2
ConfigurationName      :=Debug
WorkspacePath          := "/home/daniel/warpkern2"
ProjectPath            := "/home/daniel/warpkern2/warpkern2"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=10/09/17
CodeLitePath           :="/root/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="warpkern2.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)boost_thread $(LibrarySwitch)boost_system 
ArLibs                 :=  "boost_thread" "boost_system" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall -std=gnu++98 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall -Wc99-c11-compat $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/pca9685.cpp$(ObjectSuffix) $(IntermediateDirectory)/program.cpp$(ObjectSuffix) $(IntermediateDirectory)/socket_server.cpp$(ObjectSuffix) $(IntermediateDirectory)/general.cpp$(ObjectSuffix) $(IntermediateDirectory)/jsoncpp.cpp$(ObjectSuffix) $(IntermediateDirectory)/warpkern_rings.cpp$(ObjectSuffix) $(IntermediateDirectory)/commandline.cpp$(ObjectSuffix) $(IntermediateDirectory)/gpio.cpp$(ObjectSuffix) $(IntermediateDirectory)/presets.cpp$(ObjectSuffix) $(IntermediateDirectory)/running_leds.cpp$(ObjectSuffix) \
	



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/pca9685.cpp$(ObjectSuffix): pca9685.cpp $(IntermediateDirectory)/pca9685.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/pca9685.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pca9685.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pca9685.cpp$(DependSuffix): pca9685.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pca9685.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/pca9685.cpp$(DependSuffix) -MM "pca9685.cpp"

$(IntermediateDirectory)/pca9685.cpp$(PreprocessSuffix): pca9685.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pca9685.cpp$(PreprocessSuffix) "pca9685.cpp"

$(IntermediateDirectory)/program.cpp$(ObjectSuffix): program.cpp $(IntermediateDirectory)/program.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/program.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/program.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/program.cpp$(DependSuffix): program.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/program.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/program.cpp$(DependSuffix) -MM "program.cpp"

$(IntermediateDirectory)/program.cpp$(PreprocessSuffix): program.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/program.cpp$(PreprocessSuffix) "program.cpp"

$(IntermediateDirectory)/socket_server.cpp$(ObjectSuffix): socket_server.cpp $(IntermediateDirectory)/socket_server.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/socket_server.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/socket_server.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/socket_server.cpp$(DependSuffix): socket_server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/socket_server.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/socket_server.cpp$(DependSuffix) -MM "socket_server.cpp"

$(IntermediateDirectory)/socket_server.cpp$(PreprocessSuffix): socket_server.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/socket_server.cpp$(PreprocessSuffix) "socket_server.cpp"

$(IntermediateDirectory)/general.cpp$(ObjectSuffix): general.cpp $(IntermediateDirectory)/general.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/general.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/general.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/general.cpp$(DependSuffix): general.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/general.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/general.cpp$(DependSuffix) -MM "general.cpp"

$(IntermediateDirectory)/general.cpp$(PreprocessSuffix): general.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/general.cpp$(PreprocessSuffix) "general.cpp"

$(IntermediateDirectory)/jsoncpp.cpp$(ObjectSuffix): jsoncpp.cpp $(IntermediateDirectory)/jsoncpp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/jsoncpp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/jsoncpp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jsoncpp.cpp$(DependSuffix): jsoncpp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/jsoncpp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/jsoncpp.cpp$(DependSuffix) -MM "jsoncpp.cpp"

$(IntermediateDirectory)/jsoncpp.cpp$(PreprocessSuffix): jsoncpp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jsoncpp.cpp$(PreprocessSuffix) "jsoncpp.cpp"

$(IntermediateDirectory)/warpkern_rings.cpp$(ObjectSuffix): warpkern_rings.cpp $(IntermediateDirectory)/warpkern_rings.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/warpkern_rings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/warpkern_rings.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/warpkern_rings.cpp$(DependSuffix): warpkern_rings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/warpkern_rings.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/warpkern_rings.cpp$(DependSuffix) -MM "warpkern_rings.cpp"

$(IntermediateDirectory)/warpkern_rings.cpp$(PreprocessSuffix): warpkern_rings.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/warpkern_rings.cpp$(PreprocessSuffix) "warpkern_rings.cpp"

$(IntermediateDirectory)/commandline.cpp$(ObjectSuffix): commandline.cpp $(IntermediateDirectory)/commandline.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/commandline.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/commandline.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/commandline.cpp$(DependSuffix): commandline.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/commandline.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/commandline.cpp$(DependSuffix) -MM "commandline.cpp"

$(IntermediateDirectory)/commandline.cpp$(PreprocessSuffix): commandline.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/commandline.cpp$(PreprocessSuffix) "commandline.cpp"

$(IntermediateDirectory)/gpio.cpp$(ObjectSuffix): gpio.cpp $(IntermediateDirectory)/gpio.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/gpio.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gpio.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gpio.cpp$(DependSuffix): gpio.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gpio.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gpio.cpp$(DependSuffix) -MM "gpio.cpp"

$(IntermediateDirectory)/gpio.cpp$(PreprocessSuffix): gpio.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gpio.cpp$(PreprocessSuffix) "gpio.cpp"

$(IntermediateDirectory)/presets.cpp$(ObjectSuffix): presets.cpp $(IntermediateDirectory)/presets.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/presets.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/presets.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/presets.cpp$(DependSuffix): presets.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/presets.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/presets.cpp$(DependSuffix) -MM "presets.cpp"

$(IntermediateDirectory)/presets.cpp$(PreprocessSuffix): presets.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/presets.cpp$(PreprocessSuffix) "presets.cpp"

$(IntermediateDirectory)/running_leds.cpp$(ObjectSuffix): running_leds.cpp $(IntermediateDirectory)/running_leds.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daniel/warpkern2/warpkern2/running_leds.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/running_leds.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/running_leds.cpp$(DependSuffix): running_leds.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/running_leds.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/running_leds.cpp$(DependSuffix) -MM "running_leds.cpp"

$(IntermediateDirectory)/running_leds.cpp$(PreprocessSuffix): running_leds.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/running_leds.cpp$(PreprocessSuffix) "running_leds.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


