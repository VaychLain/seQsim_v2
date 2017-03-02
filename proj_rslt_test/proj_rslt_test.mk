##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=proj_rslt_test
ConfigurationName      :=Debug
WorkspacePath          :=/home/cnis/seQSim_v2
ProjectPath            :=/home/cnis/seQSim_v2/proj_rslt_test
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=cnis
Date                   :=18/01/17
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
ObjectsFileList        :="proj_rslt_test.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)ssl $(LibrarySwitch)crypto $(LibrarySwitch)uuid $(LibrarySwitch)pthread 
ArLibs                 :=  "libssl" "libcrypto" "libuuid" "libpthread" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/up_globals.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_helps.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_q.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_qgroup.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_qnode.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_rslt.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_SecretKeeper.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_sl.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_tfr.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) \
	



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
$(IntermediateDirectory)/up_globals.cpp$(ObjectSuffix): ../globals.cpp $(IntermediateDirectory)/up_globals.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/globals.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_globals.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_globals.cpp$(DependSuffix): ../globals.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_globals.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_globals.cpp$(DependSuffix) -MM ../globals.cpp

$(IntermediateDirectory)/up_globals.cpp$(PreprocessSuffix): ../globals.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_globals.cpp$(PreprocessSuffix)../globals.cpp

$(IntermediateDirectory)/up_helps.cpp$(ObjectSuffix): ../helps.cpp $(IntermediateDirectory)/up_helps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/helps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_helps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_helps.cpp$(DependSuffix): ../helps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_helps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_helps.cpp$(DependSuffix) -MM ../helps.cpp

$(IntermediateDirectory)/up_helps.cpp$(PreprocessSuffix): ../helps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_helps.cpp$(PreprocessSuffix)../helps.cpp

$(IntermediateDirectory)/up_q.cpp$(ObjectSuffix): ../q.cpp $(IntermediateDirectory)/up_q.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/q.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_q.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_q.cpp$(DependSuffix): ../q.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_q.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_q.cpp$(DependSuffix) -MM ../q.cpp

$(IntermediateDirectory)/up_q.cpp$(PreprocessSuffix): ../q.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_q.cpp$(PreprocessSuffix)../q.cpp

$(IntermediateDirectory)/up_qgroup.cpp$(ObjectSuffix): ../qgroup.cpp $(IntermediateDirectory)/up_qgroup.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/qgroup.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_qgroup.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_qgroup.cpp$(DependSuffix): ../qgroup.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_qgroup.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_qgroup.cpp$(DependSuffix) -MM ../qgroup.cpp

$(IntermediateDirectory)/up_qgroup.cpp$(PreprocessSuffix): ../qgroup.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_qgroup.cpp$(PreprocessSuffix)../qgroup.cpp

$(IntermediateDirectory)/up_qnode.cpp$(ObjectSuffix): ../qnode.cpp $(IntermediateDirectory)/up_qnode.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/qnode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_qnode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_qnode.cpp$(DependSuffix): ../qnode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_qnode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_qnode.cpp$(DependSuffix) -MM ../qnode.cpp

$(IntermediateDirectory)/up_qnode.cpp$(PreprocessSuffix): ../qnode.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_qnode.cpp$(PreprocessSuffix)../qnode.cpp

$(IntermediateDirectory)/up_rslt.cpp$(ObjectSuffix): ../rslt.cpp $(IntermediateDirectory)/up_rslt.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/rslt.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_rslt.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_rslt.cpp$(DependSuffix): ../rslt.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_rslt.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_rslt.cpp$(DependSuffix) -MM ../rslt.cpp

$(IntermediateDirectory)/up_rslt.cpp$(PreprocessSuffix): ../rslt.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_rslt.cpp$(PreprocessSuffix)../rslt.cpp

$(IntermediateDirectory)/up_SecretKeeper.cpp$(ObjectSuffix): ../SecretKeeper.cpp $(IntermediateDirectory)/up_SecretKeeper.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/SecretKeeper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_SecretKeeper.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_SecretKeeper.cpp$(DependSuffix): ../SecretKeeper.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_SecretKeeper.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_SecretKeeper.cpp$(DependSuffix) -MM ../SecretKeeper.cpp

$(IntermediateDirectory)/up_SecretKeeper.cpp$(PreprocessSuffix): ../SecretKeeper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_SecretKeeper.cpp$(PreprocessSuffix)../SecretKeeper.cpp

$(IntermediateDirectory)/up_sl.cpp$(ObjectSuffix): ../sl.cpp $(IntermediateDirectory)/up_sl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/sl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_sl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_sl.cpp$(DependSuffix): ../sl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_sl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_sl.cpp$(DependSuffix) -MM ../sl.cpp

$(IntermediateDirectory)/up_sl.cpp$(PreprocessSuffix): ../sl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_sl.cpp$(PreprocessSuffix)../sl.cpp

$(IntermediateDirectory)/up_tfr.cpp$(ObjectSuffix): ../tfr.cpp $(IntermediateDirectory)/up_tfr.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/tfr.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_tfr.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_tfr.cpp$(DependSuffix): ../tfr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_tfr.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_tfr.cpp$(DependSuffix) -MM ../tfr.cpp

$(IntermediateDirectory)/up_tfr.cpp$(PreprocessSuffix): ../tfr.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_tfr.cpp$(PreprocessSuffix)../tfr.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cnis/seQSim_v2/proj_rslt_test/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)main.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


