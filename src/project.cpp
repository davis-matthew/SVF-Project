//===- svf-ex.cpp -- A driver example of SVF-------------------------------------//
//
//                     SVF: Static Value-Flow Analysis
//
// Copyright (C) <2013->  <Yulei Sui>
//

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//===-----------------------------------------------------------------------===//

/*
 // A driver program of SVF including usages of SVF APIs
 //
 // Author: Yulei Sui,
 */

#include "SVF-LLVM/LLVMUtil.h"
#include "AbstractExecution/SVFIR2ItvExeState.h"
#include "Graphs/SVFG.h"
#include "WPA/Andersen.h"
#include "SVF-LLVM/SVFIRBuilder.h"
#include "Util/CommandLine.h"
#include "Util/Options.h"

using namespace std;
using namespace SVF;

int main(int argc, char ** argv)
{
    // Setup
    std::vector<std::string> moduleNameVec;
    moduleNameVec = OptionBase::parseOptions(
                        argc, argv, "Whole Program Points-to Analysis", "[options] <input-bitcode...>"
                    );

    SVFModule* svfModule = LLVMModuleSet::getLLVMModuleSet()->buildSVFModule(moduleNameVec);
    SVFIRBuilder *builder = new SVFIRBuilder(svfModule);
    SVFIR* pag = builder->build();
    ICFG* ICFG = pag->getICFG();
    ICFG->dump("icfg");
    

    // Shutdown
    AndersenWaveDiff::releaseAndersenWaveDiff();
    SVFIR::releaseSVFIR();
    SVF::LLVMModuleSet::releaseLLVMModuleSet();
    llvm::llvm_shutdown();
    return 0;
}
