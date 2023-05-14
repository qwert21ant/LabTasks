#pragma once

#include <exception>
#include <iostream>
#include <stack>
#include <variant>
#include <vector>

namespace Json {
	using std::istream;
	using std::ostream;
	using std::string;

	enum class JsonObjectType {
		Object = 0,
		Array,
		String,
		Number,
		True,
		False,
		Null
	};

	struct JsonObject;

	struct JsonField {
		string name;
		JsonObject* value;
	};

	struct JsonObject {
		JsonObjectType type;
		std::vector<JsonField> fields;

		std::variant<double, string> value;
	};

	class JsonException {
	public:
		JsonException(string expected, char meet);
		JsonException(char expect, char meet);

		string what() const;

		~JsonException() = default;

	private:
		string expected;
		char meet;
	};

	/*void read_whitespace(istream& in);
	char read_ctrl_char(istream& in);
	string read_string(istream& in);
	double read_number(istream& in);
	void read_value(istream& in, JsonObject* obj);*/

	JsonObject* read_json(istream& in);
	void remove_json(JsonObject* json);
	void print_json(ostream& out, JsonObject* json, int depth = 0);

	JsonObject* create_object();
	JsonObject* create_array();
	JsonObject* create_string(string str);
	JsonObject* create_number(double num);
	JsonObject* create_bool(bool val);
	JsonObject* create_null();

	void add_field(JsonObject* json, string field_name, JsonObject* object);
	void add_value(JsonObject* json, JsonObject* object);

	bool is_object(JsonObject*);
	bool is_array(JsonObject*);
	bool is_string(JsonObject*);
	bool is_number(JsonObject*);

	JsonObject* get_field(JsonObject* json, string field_name);

	double get_number(JsonObject*);
	string get_string(JsonObject*);
	bool get_bool(JsonObject*);
}