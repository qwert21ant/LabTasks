#include "json.h"

namespace Json {
	namespace JsonExpect {
		char CloseBrace = 1;
		char CloseSquareBracket = 1 << 1;
		char FieldName = 1 << 2;
		char Colon = 1 << 3;
		char Value = 1 << 4;
		char Comma = 1 << 5;
		char Eof = 1 << 6;
	};

	JsonException::JsonException(string expected, char meet) {
		this->expected = expected;
		this->meet = meet;
	}

	JsonException::JsonException(char expect, char meet) {
		this->meet = meet;

		if (expect & JsonExpect::CloseBrace)
			expected += '}';
		if (expect & JsonExpect::CloseSquareBracket)
			expected += ']';
		if (expect & JsonExpect::Colon)
			expected += ':';
		if (expect & JsonExpect::Comma)
			expected += ',';
		if (expect & JsonExpect::Eof)
			expected += "EOF";
		if (expect & JsonExpect::FieldName)
			expected += "FieldName";
		if (expect & JsonExpect::Value)
			expected += "Value";
	}

	string JsonException::what() const {
		if (meet == EOF)
			return string("Expected \"") + expected + "\", meet EOF";

		return string("Expected \"") + expected + "\", meet \"" + meet + "\"";
	}


	void read_whitespace(istream& in) {
		char ch;
		ch = in.peek();

		while (in && isspace(ch))
			in.get(), ch = in.peek();
	}

	char read_ctrl_char(istream& in) {
		char ch = in.get();

		if (ch == '\"') return '\"';
		if (ch == '\\') return '\\';
		if (ch == '/') return '/';
		if (ch == 'b') return '\b';
		if (ch == 'f') return '\f';
		if (ch == 'n') return '\n';
		if (ch == 'r') return '\r';
		if (ch == 't') return '\t';

		throw JsonException("\\ characters", ch);
	}

	string read_string(istream& in) {
		char ch = in.get();
		if (ch != '\"') throw JsonException("\"", ch);

		string res;

		ch = in.get();
		while (in) {
			if (ch == '\"') break;

			if (ch == '\\')
				res += read_ctrl_char(in);
			else
				res += ch;

			ch = in.get();
		}

		if (ch != '\"') throw JsonException("\"", ch);

		return res;
	}

	double read_number(istream& in) {
		double d;
		in >> d;
		return d;
	}

	void read_value(istream& in, JsonObject* obj) {
		read_whitespace(in); // ?

		char ch = in.peek();
		if (ch == '\"') {
			obj->type = JsonObjectType::String;
			obj->value = read_string(in);
		}
		else if (ch == '-' || isdigit(ch)) {
			obj->type = JsonObjectType::Number;
			obj->value = read_number(in);
		}
		else if (ch == 't') {
			char arr[4];
			in.read(arr, 4);
			if (strncmp(arr, "true", 4) == 0)
				obj->type = JsonObjectType::True;
		}
		else if (ch == 'f') {
			char arr[5];
			in.read(arr, 5);
			if (strncmp(arr, "false", 5) == 0)
				obj->type = JsonObjectType::False;
		}
		else if (ch == 'n') {
			char arr[4];
			in.read(arr, 4);
			if (strncmp(arr, "null", 4) == 0)
				obj->type = JsonObjectType::Null;
		}
		else if (ch == '{') {
			in.get();
			obj->type = JsonObjectType::Object;
		}
		else if (ch == '[') {
			in.get();
			obj->type = JsonObjectType::Array;
		}
		else
			throw JsonException("Value", ch);
	}


	void remove_json(JsonObject* json) {
		for (auto& field : json->fields)
			remove_json(field.value);
		delete json;
	}

	JsonObject* read_json(istream& in) {
		JsonObject* root = new JsonObject{};

		std::stack<JsonObject*> stack;
		stack.push(root);

		string field_name;

		try {
			read_whitespace(in);

			char ch = in.get();
			if (ch != '{')
				throw JsonException("Object", ch);

			char expect = JsonExpect::FieldName | JsonExpect::CloseBrace;

			while (true) {
				read_whitespace(in);

				ch = in.peek();
				if ((ch == '}' && expect & JsonExpect::CloseBrace) ||
					(ch == ']' && expect & JsonExpect::CloseSquareBracket)) {
					in.get();
					stack.pop();

					if (stack.empty())
						expect = JsonExpect::Eof;
					else if (stack.top()->type == JsonObjectType::Object)
						expect = JsonExpect::Comma | JsonExpect::CloseBrace;
					else if (stack.top()->type == JsonObjectType::Array)
						expect = JsonExpect::Comma | JsonExpect::CloseSquareBracket;
				}
				else if (ch == '\"' && expect & JsonExpect::FieldName) {
					field_name = read_string(in);

					expect = JsonExpect::Colon;
				}
				else if (ch == ':' && expect & JsonExpect::Colon) {
					in.get();

					expect = JsonExpect::Value;
				}
				else if (ch == ',' && expect & JsonExpect::Comma) {
					in.get();

					if (stack.top()->type == JsonObjectType::Object)
						expect = JsonExpect::FieldName;
					else if (stack.top()->type == JsonObjectType::Array)
						expect = JsonExpect::Value;
				}
				else if (!in && expect & JsonExpect::Eof) {
					break;
				}
				else if (expect & JsonExpect::Value) {
					JsonObject* obj = new JsonObject{};
					read_value(in, obj);

					stack.top()->fields.push_back({ field_name, obj });

					if (obj->type == JsonObjectType::Object) {
						stack.push(obj);

						expect = JsonExpect::FieldName | JsonExpect::CloseBrace;
					}
					else if (obj->type == JsonObjectType::Array) {
						stack.push(obj);

						expect = JsonExpect::Value | JsonExpect::CloseSquareBracket;
					}
					else {
						if (stack.top()->type == JsonObjectType::Object)
							expect = JsonExpect::Comma | JsonExpect::CloseBrace;
						else
							expect = JsonExpect::Comma | JsonExpect::CloseSquareBracket;
					}
				}
				else
					throw JsonException(expect, ch);
			}
		}
		catch (JsonException ex) {
			remove_json(root);
			throw;
		}

		return root;
	}

	void print_json(ostream& out, JsonObject* json, int depth) {
		if (!json) return;

		string offset(depth * 2, ' ');

		if (json->type == JsonObjectType::Object) {
			out << "{\n";
			if (json->fields.size()) {
				for (int i = 0; i < json->fields.size() - 1; i++) {
					out << offset << "  \"" << json->fields[i].name << "\": ";
					print_json(out, json->fields[i].value, depth + 1);
					out << ",\n";
				}
				out << offset << "  \"" << json->fields.back().name << "\": ";
				print_json(out, json->fields.back().value, depth + 1);
				out << "\n";
			}
			out << offset << "}";
		}
		else if (json->type == JsonObjectType::Array) {
			out << "[" << std::endl;
			if (json->fields.size()) {
				for (int i = 0; i < json->fields.size() - 1; i++) {
					out << offset << "  ";
					print_json(out, json->fields[i].value, depth + 1);
					out << ",\n";
				}
				out << offset << "  ";
				print_json(out, json->fields.back().value, depth + 1);
				out << "\n";
			}
			out << offset << "]";
		}
		else if (json->type == JsonObjectType::String) {
			out << "\"" << std::get<string>(json->value) << "\"";
		}
		else if (json->type == JsonObjectType::Number) {
			out << std::get<double>(json->value);
		}
		else if (json->type == JsonObjectType::True) {
			out << "true";
		}
		else if (json->type == JsonObjectType::False) {
			out << "false";
		}
		else if (json->type == JsonObjectType::Null) {
			out << "null";
		}
	}


	JsonObject* create_object() {
		JsonObject* json = new JsonObject{};
		json->type = JsonObjectType::Object;
		return json;
	}

	JsonObject* create_array() {
		JsonObject* json = new JsonObject{};
		json->type = JsonObjectType::Array;
		return json;
	}

	JsonObject* create_string(string str) {
		JsonObject* json = new JsonObject{};
		json->type = JsonObjectType::String;
		json->value = str;
		return json;
	}

	JsonObject* create_number(double num) {
		JsonObject* json = new JsonObject{};
		json->type = JsonObjectType::Number;
		json->value = num;
		return json;
	}

	JsonObject* create_bool(bool val) {
		JsonObject* json = new JsonObject{};
		if (val)
			json->type = JsonObjectType::True;
		else
			json->type = JsonObjectType::False;
		return json;
	}

	JsonObject* create_null() {
		JsonObject* json = new JsonObject{};
		json->type = JsonObjectType::Null;
		return json;
	}


	void add_field(JsonObject* json, string field_name, JsonObject* object) {
		json->fields.push_back({ field_name, object });
	}

	void add_value(JsonObject* json, JsonObject* object) {
		json->fields.push_back({ "", object});
	}

	bool is_object(JsonObject* json) {
		if (!json) return false;
		return json->type == JsonObjectType::Object;
	}

	bool is_array(JsonObject* json) {
		if (!json) return false;
		return json->type == JsonObjectType::Array;
	}

	bool is_string(JsonObject* json) {
		if (!json) return false;
		return json->type == JsonObjectType::String;
	}

	bool is_number(JsonObject* json) {
		if (!json) return false;
		return json->type == JsonObjectType::Number;
	}

	JsonObject* get_field(JsonObject* json, string field_name) {
		if (!json) return nullptr;

		for (auto& el : json->fields)
			if (el.name == field_name)
				return el.value;

		return nullptr;
	}

	double get_number(JsonObject* json) { return json ? std::get<double>(json->value) : 0.; }
	string get_string(JsonObject* json) { return json ? std::get<string>(json->value) : ""; }
	bool get_bool(JsonObject* json) { return json ? json->type == JsonObjectType::True : false; }
}