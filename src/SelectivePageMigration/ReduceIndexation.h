/* *********************************************************************
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * AND the GNU Lesser General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors of this code:
 *   Henrique Nazaré Santos  <hnsantos@gmx.com>
 *   Guilherme G. Piccoli    <porcusbr@gmail.com>
 *
 * Publication:
 *   Compiler support for selective page migration in NUMA
 *   architectures. PACT 2014: 369-380.
 *   <http://dx.doi.org/10.1145/2628071.2628077>
********************************************************************* */
#ifndef _REDUCEINDEXATION_H_
#define _REDUCEINDEXATION_H_

#include "Expr.h"
#include "LoopInfoExpr.h"

#include "llvm/Pass.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Instructions.h"

class ReduceIndexation : public FunctionPass {
public:
  static char ID;
  ReduceIndexation() : FunctionPass(ID) { }

  virtual void getAnalysisUsage(AnalysisUsage &AU) const;
  virtual bool runOnFunction(Function &F);

  bool reduceStore(StoreInst *SI, Value *&Array, Expr &Offset) const;
  bool reduceLoad(LoadInst *LI, Value *&Array, Expr &Offset)   const;
  bool reduceGetElementPtr(GetElementPtrInst *GEP, Value *&Array,
                           Expr &Offset) const;
  bool reduceMemoryOp(Value *V, Value *&Array, Expr& Offset)   const;

private:
  DataLayout *DL_;
  LoopInfoExpr *LIE_;
};

#endif

