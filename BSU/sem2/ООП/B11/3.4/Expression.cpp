#include "Expression.h"

#include <iostream>

#define LOG 0

using namespace std;

namespace Expression {
	bool ReturnValue::get_bool() const {
		if (type == ReturnType::Boolean)
			return get<bool>(value);
		else
			return bool(get<int>(value));
	}

	int ReturnValue::get_int() const {
		if (type == ReturnType::Integer)
			return get<int>(value);
		else
			return int(get<bool>(value));
	}


	IExpression::IExpression(ExpressionType expr_type) { type = expr_type; }
	ExpressionType IExpression::get_type() const { return type; }
	IExpression::~IExpression() {}


	ushort OperatorType::get_priority(ushort oper) { return oper >> 8; }

	
	IOperator::IOperator(ExpressionType expr_type, ushort expr_oper) : IExpression(expr_type) { oper = expr_oper; }
	ushort IOperator::get_oper() const { return oper; }
	IOperator::~IOperator() {}


	UnaryOperator::UnaryOperator(ushort op, IExpression* exp) : IOperator(ExpressionType::UnaryOperator, op) { operand = exp; }

	ReturnValue UnaryOperator::calc() const {
		if (oper == OperatorType::LogicNOT)
			return { ReturnType::Boolean, !operand->calc().get_bool() };
		else if (oper == OperatorType::OpenBrace)
			return operand->calc();
	}

	string UnaryOperator::print() const {
		string val = operand ? operand->print() : string("#");

		if (oper == OperatorType::OpenBrace)
			return string("(") + val + ")";
		else if (oper == OperatorType::LogicNOT)
			return string("!") + val;
	}

	IExpression* UnaryOperator::get_operand() const { return operand; }
	void UnaryOperator::set_operand(IExpression* expr) { operand = expr; }


	BinaryOperator::BinaryOperator(ushort op, IExpression* l, IExpression* r) : IOperator(ExpressionType::BinaryOperator, op) {
		left = l;
		right = r;
	}

	ReturnValue BinaryOperator::calc() const {
		ReturnValue lval = left->calc();
		ReturnValue rval = right->calc();

		if (oper == OperatorType::Less)
			return { ReturnType::Boolean, lval.get_int() < rval.get_int() };
		else if (oper == OperatorType::NoMore)
			return { ReturnType::Boolean, lval.get_int() <= rval.get_int() };
		else if (oper == OperatorType::More)
			return { ReturnType::Boolean, lval.get_int() > rval.get_int() };
		else if (oper == OperatorType::NoLess)
			return { ReturnType::Boolean, lval.get_int() >= rval.get_int() };

		else if (oper == OperatorType::Equal)
			return { ReturnType::Boolean, lval.get_int() == rval.get_int() };
		else if (oper == OperatorType::NotEqual)
			return { ReturnType::Boolean, lval.get_int() != rval.get_int() };

		else if (oper == OperatorType::LogicAND)
			return { ReturnType::Boolean, lval.get_bool() && rval.get_bool() };

		else if (oper == OperatorType::LogicOR)
			return { ReturnType::Boolean, lval.get_bool() || rval.get_bool() };
	}

	string BinaryOperator::print() const {
		string lval = left ? left->print() : string("#");
		string rval = right ? right->print() : string("#");

		string res;

		if (oper == OperatorType::Less)
			res = lval + " < " + rval;
		else if (oper == OperatorType::NoMore)
			res = lval + " <= " + rval;
		else if (oper == OperatorType::More)
			res = lval + " > " + rval;
		else if (oper == OperatorType::NoLess)
			res = lval + " >= " + rval;

		else if (oper == OperatorType::Equal)
			res = lval + " == " + rval;
		else if (oper == OperatorType::NotEqual)
			res = lval + " != " + rval;

		else if (oper == OperatorType::LogicAND)
			res = lval + " && " + rval;

		else if (oper == OperatorType::LogicOR)
			res = lval + " || " + rval;

		if (LOG)
			return "(" + res + ")";
		else
			return res;
	}

	IExpression* BinaryOperator::get_operand() const { return right; }
	void BinaryOperator::set_operand(IExpression* expr) { right = expr; }

	IExpression* Expression::BinaryOperator::get_left_operand() const { return left; }
	IExpression* Expression::BinaryOperator::get_right_operand() const { return right; }


	Value::Value(ReturnValue val) : IExpression(ExpressionType::Value) {
		value = val;
	}

	Value::Value(int val) : IExpression(ExpressionType::Value) {
		value.type = ReturnType::Integer;
		value.value = val;
	}

	Value::Value(bool val) : IExpression(ExpressionType::Value) {
		value.type = ReturnType::Boolean;
		value.value = val;
	}

	ReturnValue Value::calc() const {
		return value;
	}

	string Value::print() const {
		if (value.type == ReturnType::Integer)
			return to_string(value.get_int());

		if (value.type == ReturnType::Boolean)
			return value.get_bool() ? "true" : "false";

		return "none";
	}


	void read_whitespace(istream& in) {
		char ch = in.peek();

		while (in && isspace(ch))
			in.get(), ch = in.peek();
	}

	ushort read_operator(istream& in) {
		ushort res = 0;

		char ch = in.peek();
		if (ch == '!' || ch == '(' || ch == ')' || ch == '<' ||
			  ch == '>' || ch == '=' || ch == '&' || ch == '|') {
			char prev = in.get();
			ch = in.peek();

			if (prev == '!' && ch == '=') {
				in.get();
				res = OperatorType::NotEqual;
			}
			else if (prev == '!') {
				res = OperatorType::LogicNOT;
			}
			else if (prev == '(') {
				res = OperatorType::OpenBrace;
			}
			else if (prev == ')') {
				res = OperatorType::CloseBrace;
			}
			else if (prev == '<' && ch == '=') {
				in.get();
				res = OperatorType::NoMore;
			}
			else if (prev == '<') {
				res = OperatorType::Less;
			}
			else if (prev == '>' && ch == '=') {
				in.get();
				res = OperatorType::NoLess;
			}
			else if (prev == '>') {
				res = OperatorType::More;
			}
			else if (prev == '=' && ch == '=') {
				in.get();
				res = OperatorType::Equal;
			}
			else if (prev == '&' && ch == '&') {
				in.get();
				res = OperatorType::LogicAND;
			}
			else if (prev == '|' && ch == '|') {
				in.get();
				res = OperatorType::LogicOR;
			}
		}

		return res;
	}

	int read_int(istream& in) {
		int res = 0;

		char ch = in.peek();
		while (isdigit(ch)) {
			res = (res * 10) + (ch - '0');
			in.get();
			ch = in.peek();
		}

		return res;
	}

	ReturnValue read_value(istream& in) {
		ReturnValue res;
		res.type = ReturnType::None;

		char ch = in.peek();
		if (ch == 't') {
			char arr[4];
			in.read(arr, 4);
			if (strncmp(arr, "true", 4) == 0) {
				res.type = ReturnType::Boolean;
				res.value = true;
			}
		}
		else if (ch == 'f') {
			char arr[5];
			in.read(arr, 5);
			if (strncmp(arr, "false", 5) == 0) {
				res.type = ReturnType::Boolean;
				res.value = false;
			}
		}
		else if (isdigit(ch)) {
			res.type = ReturnType::Integer;
			res.value = read_int(in);
		}

		return res;
	}

	bool is_unary(ushort oper) {
		return
			oper == OperatorType::LogicNOT ||
			oper == OperatorType::OpenBrace ||
			oper == OperatorType::CloseBrace;
	}

	bool is_brace(IExpression* exp) {
		if (!exp)
			return false;

		if (exp->get_type() != ExpressionType::UnaryOperator)
			return false;

		return ((UnaryOperator*) exp)->get_oper() == OperatorType::OpenBrace;
	}

	bool is_value(IExpression* exp) {
		if (!exp)
			return false;

		return exp->get_type() == ExpressionType::Value;
	}

	bool is_operator(IExpression* exp) {
		if (!exp)
			return false;

		return exp->get_type() == ExpressionType::UnaryOperator || exp->get_type() == ExpressionType::BinaryOperator;
	}

	bool is_empty(IExpression* exp) {
		return ((IOperator*) exp)->get_operand() == nullptr;
	}

	string print_val(ReturnValue val) {
		if (val.type == ReturnType::Integer)
			return to_string(val.get_int());
		else if (val.type == ReturnType::Boolean)
			return val.get_bool() ? string("true") : string("false");
		else
			return string("none");
	}

	string print_oper(ushort oper) {
		if (oper == OperatorType::OpenBrace) return "(";
		else if (oper == OperatorType::CloseBrace) return ")";
		else if (oper == OperatorType::LogicNOT) return "!";
		else if (oper == OperatorType::Less) return "<";
		else if (oper == OperatorType::More) return ">";
		else if (oper == OperatorType::NoLess) return ">=";
		else if (oper == OperatorType::NoMore) return "<=";
		else if (oper == OperatorType::Equal) return "==";
		else if (oper == OperatorType::NotEqual) return "!=";
		else if (oper == OperatorType::LogicAND) return "&&";
		else if (oper == OperatorType::LogicOR) return "||";
		else return "";
	}

	void print_stack(const stack<IExpression*>& stack) {
		const auto& c = stack._Get_container();
		for (int i = 0; i < c.size(); i++)
			cout << i + 1 << ": " << c[i]->print() << endl;
	}


	void delete_expression(IExpression* exp) {
		if (!exp)
			return;

		if (exp->get_type() == ExpressionType::UnaryOperator) {
			delete_expression(((UnaryOperator*)exp)->get_operand());
		}
		else if (exp->get_type() == ExpressionType::BinaryOperator) {
			delete_expression(((BinaryOperator*)exp)->get_left_operand());
			delete_expression(((BinaryOperator*)exp)->get_right_operand());
		}

		delete exp;
	}


	void fold_stack_till_brace(stack<IExpression*>& stack) {
		if (LOG) {
			cout << "Before fold: " << endl;
			print_stack(stack);
			cout << endl;
		}

		if (stack.size() < 2)
			return;

		do {
			IExpression* exp = stack.top(); stack.pop();

			if (stack.empty())
				throw exception("fold_stack: unexpected end of stack");

			IExpression* next = stack.top();

			if (!is_operator(next))
				throw exception("fold_stack: expected operator in stack");

			bool f = is_brace(next) && is_empty(next);

			((IOperator*)next)->set_operand(exp);

			if (f)
				break;

		} while (stack.size() > 1);

		if (LOG) {
			cout << "After fold: " << endl;
			print_stack(stack);
			cout << endl;
		}
	}

	void fold_stack(stack<IExpression*>& stack, ushort priority) {
		if (LOG) {
			cout << "Priority: " << (int)priority << endl;
			cout << "Before fold: " << endl;
			print_stack(stack);
			cout << endl;
		}

		if (stack.size() < 2)
			return;


		do {
			IExpression* exp = stack.top(); stack.pop();

			if (stack.empty())
				throw exception("fold_stack: unexpected end of stack");

			IExpression* next = stack.top();

			if (!is_operator(next))
				throw exception("fold_stack: expected operator in stack");

			bool f = OperatorType::get_priority(((IOperator*) next)->get_oper()) > priority;
			
			if (LOG)
				cout << "Next priority: " << (int) OperatorType::get_priority(((IOperator*)next)->get_oper()) << endl;

			if (f) {
				stack.push(exp);
				break;
			}

			((IOperator*)next)->set_operand(exp);

		} while (stack.size() > 1);

		if (LOG) {
			cout << "After fold: " << endl;
			print_stack(stack);
			cout << endl;
		}
	}

	void clear_stack(stack<IExpression*>& stack) {
		while (!stack.empty()) {
			delete_expression(stack.top());
			stack.pop();
		}
	}

	IExpression* expression(istream& in) {
		stack<IExpression*> stack;

		try {

			stack.push(new UnaryOperator(OperatorType::OpenBrace, nullptr));

			ExpressionType last_exp = ExpressionType::UnaryOperator;
			int nBraces = 0;
			bool can_be_fold = false;

			read_whitespace(in);

			do {
				ushort oper = read_operator(in);

				if (!oper) {
					if (last_exp == ExpressionType::Value)
						throw exception("Incorrect expression");

					ReturnValue value = read_value(in);

					if (value.type == ReturnType::None)
						break; //throw exception("Expected operator or value");

					stack.push(new Value(value));
					last_exp = ExpressionType::Value;
					can_be_fold = true;
				}
				else if (oper == OperatorType::OpenBrace) {
					if (last_exp == ExpressionType::Value)
						throw exception("Incorrect expression");

					stack.push(new UnaryOperator(OperatorType::OpenBrace, nullptr));
					last_exp = ExpressionType::UnaryOperator;
					nBraces++;
					can_be_fold = false;
				}
				else if (oper == OperatorType::CloseBrace) {
					if (last_exp == ExpressionType::BinaryOperator || !nBraces || !can_be_fold)
						throw exception("Incorrect expression");

					fold_stack_till_brace(stack);
					last_exp = ExpressionType::Value;
					nBraces--;
					can_be_fold = true;
				}
				else if (is_unary(oper)) {
					if (last_exp == ExpressionType::Value)
						throw exception("Incorrect expression");

					stack.push(new UnaryOperator(oper, nullptr));
					last_exp = ExpressionType::UnaryOperator;
					can_be_fold = false;
				}
				else {
					if (!can_be_fold)
						throw exception("Incorrect expression");

					fold_stack(stack, OperatorType::get_priority(oper));

					IExpression* top = stack.top();
					stack.pop();
					stack.push(new BinaryOperator(oper, top, nullptr));
					last_exp = ExpressionType::BinaryOperator;
					can_be_fold = false;
				}

				read_whitespace(in);
			} while (!in.eof());

			if (nBraces || !can_be_fold)
				throw exception("Incorrect expression");

			if (stack.size() > 1)
				fold_stack_till_brace(stack);

		}
		catch (...) {
			clear_stack(stack);
			throw;
		}
		
		if (!is_brace(stack.top()))
			throw exception("Something went wrong");

		return ((UnaryOperator*) stack.top())->get_operand();
	}
}