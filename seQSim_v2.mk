##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=seQSim_v2
ConfigurationName      :=Debug
WorkspacePath          :=/home/cnis/seQSim_v2
ProjectPath            :=/home/cnis/seQSim_v2
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=cnis
Date                   :=22/01/17
CodeLitePath           :=/home/cnis/.codelite
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
ObjectsFileList        :="seQSim_v2.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/local/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)ssl $(LibrarySwitch)crypto $(LibrarySwitch)uuid $(LibrarySwitch)pthread $(LibrarySwitch)glib-2.0 
ArLibs                 :=  "libssl" "libcrypto" "libuuid" "pthread" "glib-2.0" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/lib/ $(LibraryPathSwitch)/usr/local/lib/openssl 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $$(pkg-config --cflags glib-2.0) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/qnode.cpp$(ObjectSuffix) $(IntermediateDirectory)/qgroup.cpp$(ObjectSuffix) $(IntermediateDirectory)/q.cpp$(ObjectSuffix) $(IntermediateDirectory)/helps.cpp$(ObjectSuffix) $(IntermediateDirectory)/rslt.cpp$(ObjectSuffix) $(IntermediateDirectory)/tfr.cpp$(ObjectSuffix) $(IntermediateDirectory)/SecretKeeper.cpp$(ObjectSuffix) $(IntermediateDirectory)/sl.cpp$(ObjectSuffix) $(IntermediateDirectory)/globals.cpp$(ObjectSuffix) \
	



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)main.cpp

$(IntermediateDirectory)/qnode.cpp$(ObjectSuffix): qnode.cpp $(IntermediateDirectory)/qnode.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/qnode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/qnode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/qnode.cpp$(DependSuffix): qnode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/qnode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/qnode.cpp$(DependSuffix) -MM qnode.cpp

$(IntermediateDirectory)/qnode.cpp$(PreprocessSuffix): qnode.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/qnode.cpp$(PreprocessSuffix)qnode.cpp

$(IntermediateDirectory)/qgroup.cpp$(ObjectSuffix): qgroup.cpp $(IntermediateDirectory)/qgroup.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/qgroup.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/qgroup.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/qgroup.cpp$(DependSuffix): qgroup.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/qgroup.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/qgroup.cpp$(DependSuffix) -MM qgroup.cpp

$(IntermediateDirectory)/qgroup.cpp$(PreprocessSuffix): qgroup.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/qgroup.cpp$(PreprocessSuffix)qgroup.cpp

$(IntermediateDirectory)/q.cpp$(ObjectSuffix): q.cpp $(IntermediateDirectory)/q.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/q.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/q.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/q.cpp$(DependSuffix): q.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/q.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/q.cpp$(DependSuffix) -MM q.cpp

$(IntermediateDirectory)/q.cpp$(PreprocessSuffix): q.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/q.cpp$(PreprocessSuffix)q.cpp

$(IntermediateDirectory)/helps.cpp$(ObjectSuffix): helps.cpp $(IntermediateDirectory)/helps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/helps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/helps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/helps.cpp$(DependSuffix): helps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/helps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/helps.cpp$(DependSuffix) -MM helps.cpp

$(IntermediateDirectory)/helps.cpp$(PreprocessSuffix): helps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/helps.cpp$(PreprocessSuffix)helps.cpp

$(IntermediateDirectory)/rslt.cpp$(ObjectSuffix): rslt.cpp $(IntermediateDirectory)/rslt.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/rslt.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/rslt.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/rslt.cpp$(DependSuffix): rslt.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/rslt.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/rslt.cpp$(DependSuffix) -MM rslt.cpp

$(IntermediateDirectory)/rslt.cpp$(PreprocessSuffix): rslt.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/rslt.cpp$(PreprocessSuffix)rslt.cpp

$(IntermediateDirectory)/tfr.cpp$(ObjectSuffix): tfr.cpp $(IntermediateDirectory)/tfr.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/tfr.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tfr.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tfr.cpp$(DependSuffix): tfr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tfr.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/tfr.cpp$(DependSuffix) -MM tfr.cpp

$(IntermediateDirectory)/tfr.cpp$(PreprocessSuffix): tfr.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tfr.cpp$(PreprocessSuffix)tfr.cpp

$(IntermediateDirectory)/SecretKeeper.cpp$(ObjectSuffix): SecretKeeper.cpp $(IntermediateDirectory)/SecretKeeper.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/SecretKeeper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SecretKeeper.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SecretKeeper.cpp$(DependSuffix): SecretKeeper.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SecretKeeper.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SecretKeeper.cpp$(DependSuffix) -MM SecretKeeper.cpp

$(IntermediateDirectory)/SecretKeeper.cpp$(PreprocessSuffix): SecretKeeper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SecretKeeper.cpp$(PreprocessSuffix)SecretKeeper.cpp

$(IntermediateDirectory)/sl.cpp$(ObjectSuffix): sl.cpp $(IntermediateDirectory)/sl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/sl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sl.cpp$(DependSuffix): sl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/sl.cpp$(DependSuffix) -MM sl.cpp

$(IntermediateDirectory)/sl.cpp$(PreprocessSuffix): sl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sl.cpp$(PreprocessSuffix)sl.cpp

$(IntermediateDirectory)/globals.cpp$(ObjectSuffix): globals.cpp $(IntermediateDirectory)/globals.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/globals.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/globals.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/globals.cpp$(DependSuffix): globals.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/globals.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/globals.cpp$(DependSuffix) -MM globals.cpp

$(IntermediateDirectory)/globals.cpp$(PreprocessSuffix): globals.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/globals.cpp$(PreprocessSuffix)globals.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


