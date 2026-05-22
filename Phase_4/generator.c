#include <assert.h>

#include "generator.h"
#include "const_tables.h"
#include "incomplete_jumps.h"

static ioperand make_number_operand(double value);

void reset_operand(ioperand *operand) {
	
	assert(operand != NULL);

	operand->type = unused_o;
	operand->val = 0;
}

void make_bool_operand(ioperand *operand, int value) {
	
	assert(operand != NULL);
	assert(value == 0 || value == 1);

	operand->type = bool_o;
	operand->val = value;
}

void make_retval_operand(ioperand *operand) {
	
	assert(operand != NULL);

	operand->type = retval_o;
	operand->val = 0;
}

void make_var_operand(Symbol *sym, ioperand *operand) {
        assert(sym != NULL);
        assert(operand != NULL);

        switch(sym->space) {
                case programvar:
                        operand->type = global_o;
                        break;
                case functionlocal:
                        operand->type = local_o;
                        break;
                case formalarg:
                        operand->type = formal_o;
                        break;
                default:
                        assert(0);
        }

        assert(sym->offset >= 0);
        operand->val = sym->offset;
}

void make_operand(Expr *expr, ioperand *operand) {
	
	assert(operand != NULL);

	if(expr == NULL) {
		reset_operand(operand);
		return;
	}

	switch(expr->type) {
		case var:
                        make_var_operand(expr->sym, operand);
                        break;

		case tableitem:
                        make_var_operand(expr->sym, operand);
                        break;

		case arithexpr:
                        make_var_operand(expr->sym, operand);
                        break;

		case boolexpr:
                        make_var_operand(expr->sym, operand);
                        break;

		case assignexpr:
                        make_var_operand(expr->sym, operand);
                        break;

		case newtable:
			make_var_operand(expr->sym, operand);
			break;

		case programfunc:
			assert(expr->sym != NULL);
			operand->type = userfunc_o;
			operand->val = new_const_userfunc(expr->sym->taddress, -1, expr->sym->name);
			break;

		case libraryfunc:
			assert(expr->sym != NULL);
			operand->type = libfunc_o;
			operand->val = new_const_libfunc(expr->sym->name);
			break;

		case constnum:
			operand->type = number_o;
			operand->val = new_const_number(expr->num_const);
			break;

		case constbool:
			make_bool_operand(operand, expr->bool_const);
			break;

		case conststring:
			assert(expr->str_const != NULL);
			operand->type = string_o;
			operand->val = new_const_string(expr->str_const);
			break;

		case nil:
			operand->type = nil_o;
			operand->val = 0;
			break;

		default:
			assert(0);
	}
}

void generate(iopcode op, Quad *quad) {
	
	Instruction instruction;

	assert(quad != NULL);

	instruction.opcode = op;
	make_operand(quad->arg1, &instruction.arg1);
	make_operand(quad->arg2, &instruction.arg2);
	make_operand(quad->res, &instruction.result);
	instruction.src_line = 0;

	quad->taddress = get_instruction_count();
	new_instruction(instruction);
}

void generate_relational(iopcode op, Quad *quad) {
	
	Instruction instruction;
	Quad *quads;
	int quad_count;

	assert(quad != NULL);

	quads = get_quads();
	quad_count = get_quad_count();

	instruction.opcode = op;
	make_operand(quad->arg1, &instruction.arg1);
	make_operand(quad->arg2, &instruction.arg2);
	instruction.result.type = label_o;
	instruction.src_line = 0;

	assert(quad->label >= 0 && quad->label <= quad_count);

	if(quad->label == quad_count) {
		instruction.result.val = 0;
		add_incomplete_jump(get_instruction_count(), quad->label);
	}
	else if(quads[quad->label].taddress >= 0)
		instruction.result.val = quads[quad->label].taddress;
	else {
		instruction.result.val = 0;
		add_incomplete_jump(get_instruction_count(), quad->label);
	}

	quad->taddress = get_instruction_count();
	new_instruction(instruction);
}

void generate_ASSIGN(Quad *quad) {
	generate(assign_i, quad);
}

void generate_ADD(Quad *quad) {
	generate(add_i, quad);
}

void generate_SUB(Quad *quad) {
	generate(sub_i, quad);
}

void generate_MUL(Quad *quad) {
	generate(mul_i, quad);
}

void generate_DIV(Quad *quad) {
	generate(div_i, quad);
}

void generate_MOD(Quad *quad) {
	generate(mod_i, quad);
}

void generate_UMINUS(Quad *quad) {
	
	Instruction instruction;
	ioperand minus_one = make_number_operand(-1);

	assert(quad != NULL);

	instruction.opcode = mul_i;
	make_operand(quad->arg1, &instruction.arg1);
	instruction.arg2 = minus_one;
	make_operand(quad->res, &instruction.result);
	instruction.src_line = 0;

	quad->taddress = get_instruction_count();
	new_instruction(instruction);
}

void generate_NEWTABLE(Quad *quad) {
	generate(newtable_i, quad);
}

void generate_TABLEGETELEM(Quad *quad) {
	generate(tablegetelem_i, quad);
}

void generate_TABLESETELEM(Quad *quad) {
	generate(tablesetelem_i, quad);
}

void generate_JUMP(Quad *quad) {
	generate_relational(jump_i, quad);
}

void generate_IF_EQ(Quad *quad) {
	generate_relational(jeq_i, quad);
}

void generate_IF_NOTEQ(Quad *quad) {
	generate_relational(jne_i, quad);
}

void generate_IF_GREATER(Quad *quad) {
	generate_relational(jgt_i, quad);
}

void generate_IF_GREATEREQ(Quad *quad) {
	generate_relational(jge_i, quad);
}

void generate_IF_LESS(Quad *quad) {
	generate_relational(jlt_i, quad);
}

void generate_IF_LESSEQ(Quad *quad) {
	generate_relational(jle_i, quad);
}

void generate_NOT(Quad *quad) {
	assert(0);
}

void generate_OR(Quad *quad) {
	assert(0);
}

void generate_AND(Quad *quad) {
	assert(0);
}

void generate_PARAM(Quad *quad) {
	
	Instruction instruction;

	assert(quad != NULL);

	instruction.opcode = pusharg_i;
	make_operand(quad->arg1, &instruction.arg1);
	reset_operand(&instruction.arg2);
	reset_operand(&instruction.result);
	instruction.src_line = 0;

	quad->taddress = get_instruction_count();
	new_instruction(instruction);
}

void generate_CALL(Quad *quad) {
	
	Instruction instruction;

	assert(quad != NULL);

	instruction.opcode = call_i;
	make_operand(quad->arg1, &instruction.arg1);
	reset_operand(&instruction.arg2);
	reset_operand(&instruction.result);
	instruction.src_line = 0;

	quad->taddress = get_instruction_count();
	new_instruction(instruction);
}

void generate_GETRETVAL(Quad *quad) {
	
	Instruction instruction;

	assert(quad != NULL);

	instruction.opcode = assign_i;
	make_operand(quad->res, &instruction.result);
	make_retval_operand(&instruction.arg1);
	reset_operand(&instruction.arg2);
	instruction.src_line = 0;

	quad->taddress = get_instruction_count();
	new_instruction(instruction);
}

void generate_FUNCSTART(Quad *quad) {
	
	Instruction instruction;

	assert(quad != NULL);
	assert(quad->res != NULL);
	assert(quad->res->sym != NULL);

	quad->res->sym->taddress = get_instruction_count();
	update_const_userfunc(quad->res->sym->taddress, -1, quad->res->sym->name);

	instruction.opcode = funcenter_i;
	make_operand(quad->res, &instruction.result);
	reset_operand(&instruction.arg1);
	reset_operand(&instruction.arg2);
	instruction.src_line = 0;

	quad->taddress = get_instruction_count();
	new_instruction(instruction);
}

void generate_RETURN(Quad *quad) {
	
	Instruction instruction;

	assert(quad != NULL);

	instruction.opcode = assign_i;
	make_retval_operand(&instruction.result);
	make_operand(quad->res, &instruction.arg1);
	reset_operand(&instruction.arg2);
	instruction.src_line = 0;

	quad->taddress = get_instruction_count();
	new_instruction(instruction);
}

void generate_FUNCEND(Quad *quad) {
	
	Instruction instruction;

	assert(quad != NULL);

	instruction.opcode = funcexit_i;
	make_operand(quad->res, &instruction.result);
	reset_operand(&instruction.arg1);
	reset_operand(&instruction.arg2);
	instruction.src_line = 0;

	quad->taddress = get_instruction_count();
	new_instruction(instruction);
}

void generate_NOP() {
	
	Instruction instruction;

	instruction.opcode = nop_i;
	reset_operand(&instruction.result);
	reset_operand(&instruction.arg1);
	reset_operand(&instruction.arg2);
	instruction.src_line = 0;

	new_instruction(instruction);
}

void generate_instruction_for_quad(Quad *quad) {
	
	static generator_func_t generators[] = {
		generate_ASSIGN,
		generate_ADD,
		generate_SUB,
		generate_MUL,
		generate_DIV,
		generate_MOD,
		generate_UMINUS,
		generate_AND,
		generate_OR,
		generate_NOT,
		generate_IF_EQ,
		generate_IF_NOTEQ,
		generate_IF_LESSEQ,
		generate_IF_GREATEREQ,
		generate_IF_LESS,
		generate_IF_GREATER,
		generate_JUMP,
		generate_CALL,
		generate_PARAM,
		generate_RETURN,
		generate_GETRETVAL,
		generate_FUNCSTART,
		generate_FUNCEND,
		generate_NEWTABLE,
		generate_TABLEGETELEM,
		generate_TABLESETELEM
	};

	assert(quad != NULL);
	assert(quad->op >= _assign && quad->op <= tablesetelem);

	generators[quad->op](quad);
}

void generate_all_instructions() {
	
	int i;
	Quad *quads = get_quads();
	int quad_count = get_quad_count();

	for(i = 0; i < quad_count; i++)
		generate_instruction_for_quad(&quads[i]);

	patch_incomplete_jumps();
}

static ioperand make_number_operand(double value) {
	
	ioperand operand;

	operand.type = number_o;
	operand.val = new_const_number(value);

	return operand;
}
