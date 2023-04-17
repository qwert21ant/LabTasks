#pragma once

#include <stack>
#include <string>
#include <sstream>
#include <variant>

using ushort = unsigned short;

namespace Expression {
	using std::istream;
	using std::ostream;
	using std::stack;
	using std::string;
	using std::variant;
	using std::get;

	enum class ReturnType {
		None    = 0,
		Integer = 1,
		Boolean = 2
	};

	struct ReturnValue {
		ReturnType type = ReturnType::None;

		variant<int, bool> value;

		bool get_bool() const;
		int get_int() const;
	};


	enum class ExpressionType {
		UnaryOperator  = 1,
		BinaryOperator = 2,
		Value          = 3
	};

	class IExpression {
	public:
		virtual ReturnValue calc() const = 0;
		virtual string print() const = 0;

		ExpressionType get_type() const;

		virtual ~IExpression();

	protected:
		IExpression(ExpressionType);

	private:
		ExpressionType type;
	};


	namespace OperatorType {
		const ushort OpenBrace  = 0xff01; // (
		const ushort CloseBrace = 0xff02; // )
		const ushort LogicNOT   = 0x0103; // !
		const ushort Less       = 0x0204; // <
		const ushort More       = 0x0205; // >
		const ushort NoLess     = 0x0206; // >=
		const ushort NoMore     = 0x0207; // <=
		const ushort Equal      = 0x0308; // ==
		const ushort NotEqual   = 0x0309; // !=
		const ushort LogicAND   = 0x040a; // &&
		const ushort LogicOR    = 0x050b; // ||

		ushort get_priority(ushort oper);
	};

	class IOperator : public IExpression {
	public:
		virtual ReturnValue calc() const = 0;
		virtual string print() const = 0;

		ushort get_oper() const;

		virtual IExpression* get_operand() const = 0;
		virtual void set_operand(IExpression*) = 0;

		virtual ~IOperator();

	protected:
		IOperator(ExpressionType, ushort);

		ushort oper;
	};

	class UnaryOperator : public IOperator {
	public:
		UnaryOperator(ushort, IExpression*);

		ReturnValue calc() const override;
		string print() const override;

		IExpression* get_operand() const override;
		void set_operand(IExpression*) override;

	private:
		IExpression* operand;
	};

	class BinaryOperator : public IOperator {
	public:
		BinaryOperator(ushort, IExpression*, IExpression*);

		ReturnValue calc() const override;
		string print() const override;

		IExpression* get_operand() const override;
		void set_operand(IExpression*) override;

		IExpression* get_left_operand() const;
		IExpression* get_right_operand() const;

	private:
		IExpression* left;
		IExpression* right;
	};

	class Value : public IExpression {
	public:
		Value(ReturnValue);
		explicit Value(int);
		explicit Value(bool);

		ReturnValue calc() const override;
		string print() const override;

	private:
		ReturnValue value;
	};


	string print_val(ReturnValue);

	IExpression* expression(istream&);

	void delete_expression(IExpression*);
}