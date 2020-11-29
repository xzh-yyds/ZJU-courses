#ifndef func_h
#define func_h
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "grammartree.h"
#include "queue"
#include <map>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>

using namespace std;
using namespace llvm;

static LLVMContext ctxt;
static IRBuilder<> builder(ctxt);
static std::map<std::string, Value*> NamedValues;
static std::map<std::string,Type *> tmap;
static std::map<std::string,Function*> fmap;
std::map<std::string,Value*> idmap;
typedef GrammarTreeNode* node;
static Instruction* someInst;
static bool isptr  = false;
std::deque<BasicBlock*> bcstk;
llvm::ValueSymbolTable* k;
// void expression(node head = nullptr,Module* m = nullptr);
// void gendecl(node head = nullptr,Mosdule* m = nullptr,bool isexternal = false);
// //return a children nodes vector
template <typename T> static std::string Print(T* value_or_type) {
    std::string str;
    llvm::raw_string_ostream stream(str);
    value_or_type->print(stream);
    return str;
}

void kprintf(Module *mod, BasicBlock *bb, const char *format, ...)
{
    Function *func_printf = mod->getFunction("printf");
    if (!func_printf) {
        PointerType *Pty = PointerType::get(IntegerType::get(mod->getContext(), 8), 0);
        FunctionType *FuncTy9 = FunctionType::get(IntegerType::get(mod->getContext(), 32), true);

        func_printf = Function::Create(FuncTy9, GlobalValue::ExternalLinkage, "printf", mod);
        func_printf->setCallingConv(CallingConv::C);

        AttributeList func_printf_PAL;
        func_printf->setAttributes(func_printf_PAL);
    }

    IRBuilder <> builder(mod->getContext());
    builder.SetInsertPoint(bb);
    string tempchar = format;
    int lenght = tempchar.length();

    Value *str = builder.CreateGlobalStringPtr(tempchar.substr(1,lenght-2));
    // cout<<Print(str)<<"   "<<format<<endl;
    std::vector <Value *> int32_call_params;
    int32_call_params.push_back(str);

    va_list ap;
    va_start(ap, format);

    // char *str_ptr = format;
    // Value *format_ptr = builder.CreateGlobalStringPtr(format);
    // int32_call_params.push_back(format_ptr);

    std::vector<llvm::Value*> extra;
    do {
        llvm::Value *op = va_arg(ap, llvm::Value*);
        //cout<<Print(op)<<endl;
        if (op->getType()!=Type::getInt1Ty(ctxt)) {
            int32_call_params.push_back(op);
        } else {
            break;
        }
    } while (1);
    va_end(ap);

    CallInst * int32_call = CallInst::Create(func_printf, int32_call_params, "call", bb);
    CallInst * returncall = CallInst::Create(func_printf,builder.CreateGlobalStringPtr("\n"),"return",bb);
}
#define oprintf(...) kprintf(__VA_ARGS__)
void gen_FOR_stmt(node head,Module*m);
void genstmt(node head ,Module* m);
void genfuncdef(node head ,Module* module );
Value* expression(node head ,Module* m );
vector<node> childs(node parent = nullptr){
    vector<node> k;
    parent =parent->left;
    // k.push_back(parent);
    while (parent)
    {
        k.push_back(parent);
        parent = parent->right;
    }
    return k;
}



//return a recursive nodes vector by a -> a,b; and b1,b2,b3,b4,b5,---
vector<node> recurchilds(node parent = nullptr){
    const string pname = parent->name;
    vector<node> store;
    while (parent->name == pname)
    {
        if(parent->left->name!=pname)
            store.push_back(parent->left);
        else{
            if(parent->left->right->name.size()!=1)
                store.push_back(parent->left->right);
            else
                store.push_back(parent->left->right->right);
        }
        parent = parent->left;
    }
    return store;

}

Value* assignment_exp(node head ,Module* m );

void genptl(vector<Type*> &ptype,vector<string>&ids,node k = nullptr){
    if(k->name==")")
        return;
    else{
        // now , k->name = parameter_type_list
        vector<node> pchilds = recurchilds(k->left);
        while (!pchilds.empty())
        {
            node topstk = pchilds.back();
            pchilds.pop_back();
            ids.push_back(topstk->left->right->left->left->content);
            // //cout<<topstk->left->left->left->content<<endl;
            ptype.push_back((tmap[topstk->left->left->left->content]));
        }
    }
}

void gendecl(node head = nullptr,Module* m = nullptr,bool isexternal = true){
    // head->name = 'declaration_specfifiers'
    // :isexternal , true means interl ,false means external
    node typenode = head->left;
    node templist = head->left->right;
    llvm:string type = head->left->left->content;
    //cout<<type<<endl;

    vector<node> kss = recurchilds(templist);


    // Value *variable = builder.CreateAlloca(builder.getInt32Ty(ctxt));
    // //将值存储到指定的位置
    // builder.CreateStore(builder.getInt32(1024), variable);

    /*
    * ksss[0] = declarator  a = 3;
    * ksss[1] = =   
    * ksss[2] = initializer b[3] = {1,2,3};
    */
    for(node item:kss){
        //cout<<item->name<<endl;
        vector<node> ksss = childs(item);
        string vname;
        int allocasize = 1;
        if(ksss[0]->left->left->right){
            vname = ksss[0]->left->left->left->content;
            node sizes = ksss[0]->left->left->right->right;
            while (sizes->name!="primary_expression")
            {
                sizes = sizes->left;
            }
            allocasize = sizes->left->intval;
            //cout<<"arrary size: "<<allocasize<<endl;
        }else{
            vname = ksss[0]->left->left->content;
        }
        if(ksss.size()==1){
            if(!isexternal){
                auto v = new GlobalVariable(static_cast<IntegerType*>(tmap[type]),
                                        false,
                                        GlobalVariable::InternalLinkage,
                                        builder.getInt32(0),
                                        vname);
                m->getGlobalList().push_back(v);
                idmap[vname] = v;
            }
            else{
                Value* v = nullptr;
                if(allocasize==1){
                    v = builder.CreateAlloca(tmap[type],nullptr,vname);
                    if(type=="int")
                        builder.CreateStore(builder.getInt32(0), v);
                    else
                        builder.CreateStore(ConstantFP::get(tmap[type],APFloat(0.0)),v);

                }else{
                    v = builder.CreateAlloca(ArrayType::get(tmap[type],allocasize));
                    if(type=="int")
                        builder.CreateMemSet(v,builder.getInt32(0),allocasize,MaybeAlign(64));
                    else
                        builder.CreateMemSet(v,ConstantFP::get(tmap[type],APFloat(0.0)),allocasize,MaybeAlign(64));
                }
                idmap[vname] = v;            
            }


        }else{
            node tempvalue = ksss[2];

            Value* rval = assignment_exp(tempvalue->left,m);
            //cout<<Print(rval)<<endl;

            while (tempvalue->name !="primary_expression")
            {
                tempvalue = tempvalue->left;
            }
            //cout<<tempvalue->left->intval<<endl;
            if(!isexternal){
                if(tempvalue->left->name =="CONSTANT_INT"){
                    auto v = new GlobalVariable(static_cast<IntegerType*>(tmap[type]),
                                                false,
                                                GlobalVariable::InternalLinkage,
                                                builder.getInt32(tempvalue->left->intval),
                                                vname);
                    m->getGlobalList().push_back(v);
                    idmap[vname] = v;
                }else{
                    Constant* tempvaluedf = ConstantFP::get(ctxt,APFloat(tempvalue->left->douval));
                    auto v = new GlobalVariable(static_cast<IntegerType*>(tmap[type]),
                                                false,
                                                GlobalVariable::InternalLinkage,
                                                tempvaluedf,
                                                vname);
                    m->getGlobalList().push_back(v);
                    idmap[vname] = v;
                }
            }else{
                Value* v = nullptr;
                if(type=="int"){
                    v = allocasize==1 ? 
                            builder.CreateAlloca(Type::getInt32Ty(ctxt)):
                            builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(ctxt),allocasize));
                    if(allocasize==1){
                        builder.CreateStore(rval, v);
                    }else{
                        builder.CreateMemSet(v,rval,allocasize,MaybeAlign(16));
                    }
                }
                else{
                    if(allocasize==1){
                        v = builder.CreateAlloca(Type::getDoubleTy(ctxt));
                        builder.CreateStore(rval,v);
                    }else{
                        v = builder.CreateAlloca(ArrayType::get(Type::getDoubleTy(ctxt),allocasize));
                        builder.CreateMemSet(v,rval,allocasize,MaybeAlign(64));
                    }
                }
                idmap[vname] = v;
                v->setName(vname);
            }
        }
        //cout<<vname<<":"<<Print(idmap[vname])<<endl;
    }

}

Value* primary_exp(node head = nullptr,Module* m = nullptr ){

    //cout<<"here,i am" << head->name<<endl;
    // head = head->left;
    if(head->left->name=="IDENTIFIER"){
        Value* k = idmap[head->left->content];
        //cout<<"k:"<<Print(k)<<endl;
        isptr = true;
        return k;
    }else if(head->left->name == "CONSTANT_INT"){
        isptr = false;
        return builder.getInt32(head->left->intval);
    }else if(head->left->name == "CONSTANT_DOUBLE"){
        isptr = false;
        return ConstantFP::get(ctxt,APFloat(head->left->douval));
    }else{
        isptr = false;
        return builder.getInt32(0);
    }
}
Value* postfix_exp(node head = nullptr ,Module* m = nullptr){
    if(head->left->right){
        // node ifcon = head->left->right;
        // func(a,b);
        string callname ;
        string idname = head->left->right->name;
        node id = head->left->right->right;
        if(idname=="("){
            // 函数
            callname = head->left->content;
            Function* funccall = fmap[callname];
            vector<Value*> func_args;
            vector<node> args = recurchilds(head->left->right->right);

            while (!args.empty())
            {
                node topitem = args.back();
                Value* argv = assignment_exp(topitem,m);
                func_args.push_back(argv);

                args.pop_back();
            }
            

            return builder.CreateCall(funccall,func_args);
        }else if(idname =="["){
            // 数组
            callname = head->left->left->left->content;
            Value* idx = expression(id,m);
            //cout<<"idx :"<<Print(idx)<<endl;
            Value* arr = idmap[callname];
            //cout<<"arr :"<<Print(arr)<<endl;
            Value* ret = builder.CreateInBoundsGEP(arr,idx);
            //cout<<"ret :"<<Print(ret)<<endl;
            return ret;
        }else{
            return builder.getInt32(0);

        }
    }else{
        return primary_exp(head->left,m);
    }
}
Value* unary_exp(node head = nullptr, Module* m  =  nullptr){
    if(head->left->right){
        return postfix_exp(head->left,m);

    }else{
        return postfix_exp(head->left,m);
    }
}
Value* cast_exp(node head = nullptr,Module* m = nullptr){
    return unary_exp(head->left,m);
}
Value* multiplicative_exp(node head = nullptr, Module* m = nullptr){
    if(head->left->right){
        Value* l = multiplicative_exp(head->left,m);
        Value* lval = isptr?builder.CreateLoad(l):l;
        Value* r = cast_exp(head->left->right->right);
        Value* rval = isptr?builder.CreateLoad(r):r;
        isptr = false;
        if(head->left->right->name=="*")
            if(head->vtype=="int"){
                return builder.CreateMul(lval,rval);
            }else{
                return builder.CreateFMul(lval,rval);
            }
        else if(head->left->right->name=="/")
            if(head->vtype=="int"){
                // 整数除法
                return builder.CreateSDiv(lval,rval);
            }else
                return builder.CreateFDiv(lval,rval);
        else {
            // Value* quotient = builder.CreateSDiv(lval,rval);
            // Value* multiquo = builder.CreateMul(quotient,r);
            // return builder.CreateSub(l,multiquo);
            return builder.CreateSRem(lval,rval);
        }
    }else{
        return cast_exp(head->left,m);
    }
}
Value* additive_exp(node head = nullptr, Module* m = nullptr){
    if(head->left->right){
        Value* l = additive_exp(head->left,m);
        Value* lval = isptr?builder.CreateLoad(l):l;
        Value* r = multiplicative_exp(head->left->right->right);
        Value* rval = isptr?builder.CreateLoad(r):r;
        string type = head->vtype;
        isptr =false;
        if(head->left->right->name=="+"){
            if(type=="int")
                return builder.CreateAdd(lval,rval);
            else
                return builder.CreateFAdd(lval,rval);
        }else{
            if(type=="int")
                return builder.CreateSub(lval,rval);
            else
                return builder.CreateFSub(lval,rval);
        }
    }else{
        return multiplicative_exp(head->left,m);
    }
}
Value* shift_exp(node head = nullptr,Module* m = nullptr){
    if(head->left->right){
        //(bool)? v1: v2
        // Value* ifcondi = 
        return postfix_exp(head->left,m);

    }else{
        return additive_exp(head->left,m);
    }
}
Value* relational_exp(node head = nullptr, Module* m = nullptr){
    if(head->left->right){
        Value* l = relational_exp(head->left,m);
        Value* lval = isptr ? builder.CreateLoad(l) : l;
        Value* r = shift_exp(head->left->right->right,m);
        Value* rval = isptr ? builder.CreateLoad(r) : r;
        node op = head->left->right;
        if(op->name =="<"){
            return lval->getType()==Type::getInt32Ty(ctxt)? 
                        builder.CreateICmpSLT(lval,rval,"less"):
                        builder.CreateFCmpOLT(lval,rval,"less");
        }else if(op->name == ">"){
            return lval->getType()==Type::getInt32Ty(ctxt)?
                        builder.CreateICmpSGT(lval,rval,"greater"):
                        builder.CreateFCmpOGT(lval,rval,"greater");
        }else if(op->name == "OP_LE"){
            return lval->getType()==Type::getInt32Ty(ctxt)?
                        builder.CreateICmpSLE(lval,rval,"LE"):
                        builder.CreateFCmpOLE(lval,rval,"LE");
        }else{
            return lval->getType()==Type::getInt32Ty(ctxt)?
                        builder.CreateICmpSGE(lval,rval,"GE"):
                        builder.CreateFCmpOGE(lval,rval,"GE");
        }
    }else{
        return shift_exp(head->left,m);
    }
}
Value* equality_exp(node head = nullptr, Module* m = nullptr){
    if(head->left->right){
        Value* l = equality_exp(head->left,m);
        Value* lval = isptr ? builder.CreateLoad(l) : l;

        Value* r = relational_exp(head->left->right->right,m);
        Value* rval = isptr ? builder.CreateLoad(r) : r;

        if(head->left->right->name=="OP_EQ"){
            Value* k =  builder.CreateICmpEQ(lval,rval,"ifequal");
            //cout<<Print(k)<<endl;
            return k;
        }else{
            return builder.CreateICmpNE(lval,rval,"ifnotequal");
        }
    }
    else {
        return relational_exp(head->left,m);
    }
}
Value* and_exp(node head = nullptr,Module* m = nullptr){
    if(head->left->right){
        return equality_exp(head->left,m);

    }else{
        return equality_exp(head->left,m);
    }
}
Value* exclusive_or_exp(node head = nullptr, Module* m = nullptr){
    if(head->left->right){
        return and_exp(head->left,m);
    }else
    {
        return and_exp(head->left,m);
    }
    
}
Value* inclusive_or_exp(node head = nullptr, Module* m = nullptr){
    if(head->left->right){
        return exclusive_or_exp(head->left,m);

    }else
        return exclusive_or_exp(head->left,m);
}
Value* logic_and_exp(node head = nullptr,Module* m = nullptr){
    if(head->left->right){
        return inclusive_or_exp(head->left,m);

    }else
    {
        return inclusive_or_exp(head->left,m);
    }
    
}

Value* logic_or_exp(node head = nullptr, Module* m = nullptr){
    //cout<<"expresssion: "<<head->name<<endl;

    if(head->left->right){
        return logic_and_exp(head->left,m);
    }else
        return logic_and_exp(head->left,m);
}

Value* conditional_exp(node head = nullptr,Module* m = nullptr){
    //cout<<"expresssion: "<<head->name<<endl;

    if(head->left->right){
        // // builder.CreateICmp();
        Value* condition = logic_or_exp(head->left,m);
        // condition = builder.CreateICmpNE(condition,ConstantInt::get(builder.getInt32Ty(),0),"ifcond");
        // // condition->getRawSubclassOptionalData();
        if(condition->getRawSubclassOptionalData()!=0)
            return conditional_exp(head->left->right->right->right->right,m);
        else
        {
            return conditional_exp(head->left->right->right,m);
        }        
    }else{
        return logic_or_exp(head->left,m);
    }
}

Value* assignment_exp(node head = nullptr,Module* m = nullptr){
    //cout<<"expressddsion: "<<head->name<<endl;

    if(head->left->name == "unary_expression"){
        // //cout<<"hel"<<head->left->name<<endl;
        Value* lv =  unary_exp(head->left);
        Value* lval = builder.CreateLoad(lv);
        Value* rv =  assignment_exp(head->left->right->right,m);
        // Value* rval = isptr? builder.CreateLoad(rv):rv;
        Value* rval = rv;
        //cout<<"heeeeee"<<Print(lval)<<" "<<Print(rval)<<endl;
        Value* temp = nullptr;
        // //cout<<Print(lv)<<"\n"<<Print(rv)<<endl;
        string op = head->left->right->left->name;
        if(op=="="){
            temp = rv;
        }else if(op=="ASSIGN_ADD"){
            //+=
            temp = (lval->getType()==Type::getInt32Ty(ctxt))? 
                                    builder.CreateAdd(lval,rval):
                                    builder.CreateFAdd(lval,rval);
        }else if(op=="ASSIGN_SUB"){
            temp = (lval->getType()==Type::getInt32Ty(ctxt))?
                                    builder.CreateSub(lval,rval):
                                    builder.CreateFSub(lval,rval);
        }else if(op=="ASSIGN_MUL"){
            temp = (lval->getType()==Type::getInt32Ty(ctxt))?
                                    builder.CreateMul(lval,rval):
                                    builder.CreateFMul(lval,rval);
        }else if(op=="ASSIGN_DIV"){
            temp = (lval->getType()==Type::getInt32Ty(ctxt))?
                                    builder.CreateSDiv(lval,rval):
                                    builder.CreateFDiv(lval,rval);

        }else if(op=="ASSIGN_MOD"){
            temp = (lval->getType()==Type::getInt32Ty(ctxt))?
                                    builder.CreateSRem(lval,rval):
                                    builder.CreateFRem(lval,rval);
        }else if(op=="ASSIGN_LEFTSHIFT"){
            temp = (lval->getType()==Type::getInt32Ty(ctxt))?
                                    builder.CreateShl(lval,rval):
                                    builder.CreateShl(lval,rval);            
        }else if(op=="ASSIGN_RIGHTSHIFT"){
            temp = (lval->getType()==Type::getInt32Ty(ctxt))?
                                    builder.CreateAShr(lval,rval):
                                    builder.CreateLShr(lval,rval); 
        }else if(op=="ASSIGN_AND"){
            // temp = (lval->getType()==Type::getInt32Ty(ctxt))?
            //                         builder.CreateShl(lval,rval):
            //                         builder.CreateShl(lval,rval); 
            temp = builder.CreateAnd(lval,rval);
        }else if(op=="ASSIGN_Xor"){
            temp = builder.CreateXor(lval,rval);
        }else{
            // op = "ASSIGN_Or"
            temp = builder.CreateOr(lval,rval);
        }

        builder.CreateStore(temp,lv);
        //cout<<"store done"<<endl;
        return builder.CreateLoad(lv);
    }else{
        Value* tret =  conditional_exp(head->left, m);
        return isptr? builder.CreateLoad(tret) :tret;
        // return tret;
    }
}

Value* expression(node head = nullptr,Module* m = nullptr){
    // expression -> expression,assignment_expression
    // cout<<"expresssion: "<<head->name<<endl;
    vector<node> explists = recurchilds(head);
    Value* ret = nullptr;
    while (!explists.empty())
    {
        node temp  = explists.back();   //temp->name = "assignment_expression"

        // cout<<temp->name<<endl;
        // cout<<"hello,how are you"<<endl;

        // vector<node> assignchilds = childs(temp);
        
        ret =  assignment_exp(temp,m);


        explists.pop_back();
    }
    return ret;
}

void selection_statement(node head = nullptr,Module* m = nullptr){
    // head->name = "IF" or "Switch";
    node ifcond = head->right->right;
    Value* ifval = equality_exp(ifcond,m);
    // builder.CreateStore(ifval,kk);
    // cout<<ifval->getRawSubclassOptionalData()<<endl;
    if(head->name == "IF"){

        if(head->right->right->right->right->right){
            //if-else
            // cout<<Print(ifval)<<endl;
            Function *TheFunction = builder.GetInsertBlock()->getParent();
            BasicBlock* curr = builder.GetInsertBlock();
            BasicBlock* thenBB = BasicBlock::Create(ctxt, "then",TheFunction);
            BasicBlock* elseBB = BasicBlock::Create(ctxt, "else",TheFunction);
            builder.CreateCondBr(ifval, thenBB, elseBB);

            builder.SetInsertPoint(thenBB);
            // builder.setinsertb
            //insert stuff

            genstmt(head->right->right->right->right,m);
            // Value* sddsss = builder.CreateAlloca(Type::getInt32Ty(ctxt));


            builder.SetInsertPoint(elseBB);
            //insert stuff
            genstmt(head->right->right->right->right->right->right,m);
            // Value* sdsdsaa = builder.CreateAlloca(Type::getInt32Ty(ctxt));
            builder.SetInsertPoint(curr);
            // Value* sdssssss = builder.CreateAlloca(Type::getInt32Ty(ctxt));
            
        }else{
            //pure if
        }

    }else{
        // switch-case selection_statement;

    }
}
Value* gen_expr_stmt(node head = nullptr,Module* m = nullptr){
    if(head->left->name==";"){
        return expression(head,m);

    }else if(head->left->name=="expression"){
        return expression(head,m);
    }else{
        return builder.getInt32(0);
    }
}

void gen_FOR_stmt(node head = nullptr,Module* m = nullptr){
    if(head->left->name=="expression_statement"){
        node expr_stmt1=head->left->right->right;
        node expr_stmt2=expr_stmt1->right;
        if(expr_stmt2->right->name==")"){
            node stmt=expr_stmt2->right->right;
            Value* loopcondition = builder.getInt1(false);
            Function *TheFunction = builder.GetInsertBlock()->getParent();
            //获得插入的点
            BasicBlock *BC = builder.GetInsertBlock();
            //这里就是将loop:给插入到TheFunction当中
            BasicBlock *LoopBB = BasicBlock::Create(ctxt, "loop", TheFunction);
            BasicBlock *CondBB = BasicBlock::Create(ctxt,"con",TheFunction);
            BasicBlock *AfteBB = BasicBlock::Create(ctxt,"outer",TheFunction);
            bcstk.push_back(CondBB);
            bcstk.push_back(LoopBB);
            bcstk.push_back(AfteBB);
            // LoopBB->

            gen_expr_stmt(expr_stmt1,m);

            builder.CreateBr(CondBB);
            //设置插入点为loop块
            builder.SetInsertPoint(CondBB);
            loopcondition = gen_expr_stmt(expr_stmt2,m);
            builder.CreateCondBr(loopcondition,LoopBB,AfteBB);

            builder.SetInsertPoint(LoopBB);
            genstmt(stmt,m);
            builder.CreateBr(CondBB);

            builder.SetInsertPoint(AfteBB);
        }else if(expr_stmt2->right->name=="expression"){
            node expr=expr_stmt2->right;
            node stmt=expr->right->right;
            Value* loopcondition = builder.getInt1(false);
            Function *TheFunction = builder.GetInsertBlock()->getParent();
            //获得插入的点
            BasicBlock *BC = builder.GetInsertBlock();
            //这里就是将loop:给插入到TheFunction当中
            BasicBlock *LoopBB = BasicBlock::Create(ctxt, "loop", TheFunction);
            BasicBlock *CondBB = BasicBlock::Create(ctxt,"con",TheFunction);
            BasicBlock *AfteBB = BasicBlock::Create(ctxt,"outer",TheFunction);
            bcstk.push_back(CondBB);
            bcstk.push_back(LoopBB);
            bcstk.push_back(AfteBB);
            // LoopBB->

            gen_expr_stmt(expr_stmt1,m);

            builder.CreateBr(CondBB);
            //设置插入点为loop块
            builder.SetInsertPoint(CondBB);
            loopcondition = expression(expr_stmt2,m);
            builder.CreateCondBr(loopcondition,LoopBB,AfteBB);

            builder.SetInsertPoint(LoopBB);
            genstmt(stmt,m);
            expression(expr);
            builder.CreateBr(CondBB);

            builder.SetInsertPoint(AfteBB);
        }
    }else if(head->left->name=="declaration"){
        node decl=head->left->right->right;
        node expr_stmt=decl->right;
        if(expr_stmt->right->name==")"){
            node stmt=expr_stmt->right->right;
            Value* loopcondition = builder.getInt1(false);
            Function *TheFunction = builder.GetInsertBlock()->getParent();
            //获得插入的点
            BasicBlock *BC = builder.GetInsertBlock();
            //这里就是将loop:给插入到TheFunction当中
            BasicBlock *LoopBB = BasicBlock::Create(ctxt, "loop", TheFunction);
            BasicBlock *CondBB = BasicBlock::Create(ctxt,"con",TheFunction);
            BasicBlock *AfteBB = BasicBlock::Create(ctxt,"outer",TheFunction);
            bcstk.push_back(CondBB);
            bcstk.push_back(LoopBB);
            bcstk.push_back(AfteBB);
            // LoopBB->

            gendecl(decl,m);

            builder.CreateBr(CondBB);
            //设置插入点为loop块
            builder.SetInsertPoint(CondBB);
            loopcondition = gen_expr_stmt(expr_stmt,m);
            builder.CreateCondBr(loopcondition,LoopBB,AfteBB);

            builder.SetInsertPoint(LoopBB);
            genstmt(stmt,m);
            builder.CreateBr(CondBB);

            builder.SetInsertPoint(AfteBB);
        }else if(expr_stmt->right->name=="expression"){
            node expr=expr_stmt->right;
            node stmt=expr->right->right;
            Value* loopcondition = builder.getInt1(false);
            Function *TheFunction = builder.GetInsertBlock()->getParent();
            //获得插入的点
            BasicBlock *BC = builder.GetInsertBlock();
            //这里就是将loop:给插入到TheFunction当中
            BasicBlock *LoopBB = BasicBlock::Create(ctxt, "loop", TheFunction);
            BasicBlock *CondBB = BasicBlock::Create(ctxt,"con",TheFunction);
            BasicBlock *AfteBB = BasicBlock::Create(ctxt,"outer",TheFunction);
            bcstk.push_back(CondBB);
            bcstk.push_back(LoopBB);
            bcstk.push_back(AfteBB);
            // LoopBB->

            gendecl(decl,m);

            builder.CreateBr(CondBB);
            //设置插入点为loop块
            builder.SetInsertPoint(CondBB);
            loopcondition = expression(expr_stmt,m);
            builder.CreateCondBr(loopcondition,LoopBB,AfteBB);

            builder.SetInsertPoint(LoopBB);
            gen_expr_stmt(stmt,m);
            expression(expr);
            builder.CreateBr(CondBB);

            builder.SetInsertPoint(AfteBB);
        }
    }
}
void iteration_statement(node head = nullptr,Module* m = nullptr){
    //head->name = "iteration_statement"
    if(head->left->name=="WHILE"){
        //While(){}循环
        Value* loopcondition = builder.getInt1(false);
        Function *TheFunction = builder.GetInsertBlock()->getParent();
        //获得插入的点
        BasicBlock *BC = builder.GetInsertBlock();
        //这里就是将loop:给插入到TheFunction当中
        BasicBlock *LoopBB = BasicBlock::Create(ctxt, "loop", TheFunction);
        BasicBlock *CondBB = BasicBlock::Create(ctxt,"con",TheFunction);
        BasicBlock *AfteBB = BasicBlock::Create(ctxt,"outer",TheFunction);
        bcstk.push_back(CondBB);
        bcstk.push_back(LoopBB);
        bcstk.push_back(AfteBB);
        // LoopBB->

        builder.CreateBr(CondBB);
        //设置插入点为loop块
        builder.SetInsertPoint(CondBB);
        loopcondition = expression(head->left->right->right,m);
        builder.CreateCondBr(loopcondition,LoopBB,AfteBB);

        builder.SetInsertPoint(LoopBB);
        genstmt(head->left->right->right->right->right,m);
        builder.CreateBr(CondBB);

        builder.SetInsertPoint(AfteBB);

    }else{
        //For循环
        gen_FOR_stmt(head,m);

    }
}
void jump_statement(node head = nullptr,Module* m = nullptr){
    //head -> name = break;continue;return;
    string s = head->left->name;
    if(s=="BREAK"){
        BasicBlock* currbc = builder.GetInsertBlock();
        for(int i = 0;i<bcstk.size();i++){
            if(currbc==bcstk[i]){
                builder.CreateBr(bcstk[i+1]);
                return;
            }
        }
    }else if(s=="CONTINUE"){
        BasicBlock* currbc = builder.GetInsertBlock();
        for(int i = 0;i<bcstk.size();i++){
            if(currbc==bcstk[i]){
                builder.CreateBr(bcstk[i+1]);
                return;
            }
        }
    }else{
        // name = return 0
        if(head->left->right->right){
            Value* ret = expression(head->left->right,m);
            builder.CreateRet(ret);
        }else{
            builder.CreateRetVoid();
        }
        return ;
    }
}
void print_statement(node head = nullptr,Module* m = nullptr){
    node formats = head->left->right->right;
    node printval = head->left->right->right->right->right;
    Value* pval = expression(printval);
    // vector<Value*> funcargs;
    // funcargs.push_back(format);
    // funcargs.push_back(pval);
    BasicBlock* curr = builder.GetInsertBlock();
    #define llvm_printf(...) oprintf(m, curr, __VA_ARGS__, builder.getInt1(true))
    llvm_printf(formats->content.c_str(),pval);
    // Function* printfunc = module->
}

void genstmt(node head = nullptr,Module* m = nullptr){
    // head->naem = "statement"
    // cout<<"here statement:  "<<endl;here statement
    string s = head->left->name;
    // cout<<s<<endl;
    head = head->left;
    if(s=="expression_statement"){
        if(head->left->name ==";"){ 
            return;
        }else
        {
            //expression
            expression(head->left,m);
        }
        

    }else if(s=="selection_statement"){

        selection_statement(head->left,m);

    }else if(s=="iteration_statement"){
        iteration_statement(head,m);
    }else if(s=="compound_statement"){

        genfuncdef(head,m);
    }else if(s=="jump_statement"){
        //s = jump_statement
        jump_statement(head,m);
    }else{
        // s = print_statement;
        print_statement(head,m);
    }
}
void genfuncdef( node head = nullptr,Module* module = nullptr){
    // generate the codes for block_item in the compound_statement
    // head->name = "compound_statement"
    // cout<<head->name<<endl;
    node ptr = head->left->right;
    // cout<<ptr->name<<endl;
    vector<node> blkitems = recurchilds(ptr);

    while(!blkitems.empty()){
        node itemptr = blkitems.back();     // item->ptr->name = "block_item"
        // cout<<itemptr->name<<endl;
        if(itemptr->left->name=="declaration"){
            gendecl(itemptr->left,module);
        }else{
            //itemptr->name = "statement"
            genstmt(itemptr->left,module);
        }

        blkitems.pop_back();
    }

}

void genfunc(node head = nullptr,Module* module = nullptr){
    std::vector<Type*> param_type;
    std::vector<std::string> ids;
    //cout<head->name<<endl;
    head = head->left;
    //cout<head->right->name<<endl;

    string rettype = head->left->left->content;
    //cout<"rettype: "<<rettype<<endl;

    string funcname = head->right->left->left->left->content;
    //cout<"func: "<<funcname<<endl;
    node ptl = head->right->left->left->right->right;

    if(ptl->name!=")")
        genptl(param_type,ids,ptl);

    //use the arguments from the function

    FunctionType* functp = FunctionType::get(builder.getInt32Ty(),param_type,false);
    Function* func = Function::Create(functp,Function::ExternalLinkage,funcname,module);
    BasicBlock* fbc = BasicBlock::Create(ctxt,"entry",func);

    fmap[funcname] = func;

    builder.SetInsertPoint(fbc);
    // builder.getinser
    for(auto& arg : func->args()){
        static int cnt = 0;
        Value* tp = &arg;
        string name = ids[cnt++];
        //cout<"name:   "<<name<<endl;
        //cout<"args: "<<Print(tp)<<endl;
        Value* temparg = builder.CreateAlloca(tp->getType());
        temparg->setName(name);
        builder.CreateStore(tp,temparg);
        idmap[name] = temparg;
    }
        // arg.setName("sdf");
    // if(ptl->left->name!="{")
    genfuncdef(head->right->right,module);

    // builder.CreateCall()

    // Value* k = builder.CreateAlloca(tmap[rettype]);
    // builder.CreateStore(builder.getInt32(580),k);
    fmap[funcname] = func;
}

void gen(GrammarTreeNode* head=nullptr,string filename = "a"){
    tmap[string("int")] = Type::getInt32Ty(ctxt);
    tmap[string("bool")] = Type::getInt1Ty(ctxt);
    tmap[string("double")] = Type::getDoubleTy(ctxt);
    tmap[string("float")] = Type::getFloatTy(ctxt);

    // std::shared_ptr<Module> moadule(new Module(filename,ctxt));
    static Module* module = new Module(filename,ctxt);

    stack<GrammarTreeNode*> kt;
    node temp = head->left;
    while (temp->name=="translation_unit")
    {
        if(temp->left->name=="translation_unit")
            kt.push(temp->left->right);
        else{
            kt.push(temp->left);
        }
        temp=temp->left;
    }
    while (!kt.empty())
    {
        node k = kt.top();

        if(k->left->name=="function_definition"){
            //cout<k->left->name<<endl;
            genfunc(k->left,(module));

        }
        else{
            //cout<k->left->name<<endl;
            gendecl(k->left,module,false);
  
        }
        // string vn = "k";
        // Value* kd = idmap[vn];
        // cout<< Print(kd)<<endl;
        kt.pop();
    }

    // output the IR codes stored in module to *.ll file
    raw_ostream *out = &outs();
    std::error_code EC;
    out = new raw_fd_ostream(filename+".ll",EC,sys::fs::F_None);
    module->print(*out, nullptr);
    delete out;
}

void treePrint(GrammarTreeNode *node, int level)
{
    if (node == NULL)
    {
        return;
    }
    string name = node->name;
    if (node->line_no == -1)
    {
        treePrint(node->left, level + 1);
        treePrint(node->right, level);
        return;
    }
    for (int i = 0; i < level; i++)
    {
        cout << "| ";
    }
    cout << node->name;
    if (node->name == "IDENTIFIER" || node->name == "BOOL" || node->name == "INT" || node->name == "CHAR" || node->name == "DOUBLE")
    {
        cout << ":" << node->content;
    }
    else if (node->name == "CONSTANT_INT" || node->name == "CONSTANT_DOUBLE")
    {
        // cout<<node->content<<endl;
        cout << ":" << node->content << " ";
    }
    else if (node->name == "TRUE" || node->name == "FALSE")
    {
        cout << ":" << node->content << " ";
    }
    else if (node->name == "STRING_LITERAL")
    {
        cout << ":" << node->content;
    }
    else
    {
        cout << "   <@" << node->line_no << ">";
    }
    cout << endl;
    treePrint(node->left, level + 1);
    treePrint(node->right, level);
};

void treeNodeFree(GrammarTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    treeNodeFree(node->left);
    treeNodeFree(node->right);
    delete node;
};

void printtree(GrammarTreeNode *head){
    static int cnt = 0;
    if(!head)
        return;
    cnt++;
    for (int i = 0;i<cnt-1;i++)
        cout << "|  ";
    cout << head->name << endl;
    printtree(head->left);
    cnt--;
    printtree(head->right);
}

string int2string(int a)
{
    if (a == 0)
        return "0";
    string ret = "";
    while (a)
    {
        int t = a % 10;
        a /= 10;
        char c[] = "0";
        c[0] += t;
        ret = string(c) + ret;
    }
    return ret;
}

GrammarTreeNode *treeCreate(std::string name, int arg_cnt, ...)
{
    va_list valist;
    GrammarTreeNode *head = new GrammarTreeNode();
    if (!head)
    {
        printf("out of space\n");
        exit(0);
    }

    GrammarTreeNode *tmp = NULL;
    head->name = name;
    va_start(valist, arg_cnt);
    if (arg_cnt > 0)
    {
        tmp = va_arg(valist, GrammarTreeNode *);
        head->left = tmp;
        head->line_no = tmp->line_no;
        if (arg_cnt == 1)
        {
            head->content = tmp->content;
            head->vtype = tmp->vtype;
        }
        else
        {
            int doublecnt = 0;
            for (int i = 1; i < arg_cnt; i++)
            {
                doublecnt+= (int)(tmp->name=="double");
                tmp->right = va_arg(valist, GrammarTreeNode *);
                tmp = tmp->right;
            }
            if(doublecnt)
                head->vtype = "double";
        }
    }
    else if (arg_cnt == 0)
    {
        // the following para is the current line number
        int ln = va_arg(valist, int);
        head->line_no = ln;
        if (head->name == "CONSTANT_INT")
        {
            int int_value;
            if (strlen(yytext) > 1 && yytext[0] == 0 && yytext[1] != 'x')
            {
                sscanf(yytext, "%o", &int_value);
            }
            else if (strlen(yytext) > 1 && yytext[0] == 0 && yytext[1] == 'x')
            {
                sscanf(yytext, "%x", &int_value);
            }
            else
            {
                int_value = atoi(yytext);
            }
            // cout<<int_value<<endl;
            head->content = int2string(int_value);
            head->intval = int_value;
            // std:://cout<"hello,12211111"<<std::endl;
        }
        else if (head->name == "CONSTANT_DOUBLE")
        {
            head->content = yytext;
        }
        else if (head->name == "TRUE")
        {
            head->content = int2string(1);
        }
        else if (head->name == "FALSE")
        {
            head->content = int2string(0);
        }
        else if (head->name == "STRING_LITERAL")
        {
            head->content = yytext;
        }
        else
        {
            head->content = yytext;
        }
    }
    return head;
};
#endif