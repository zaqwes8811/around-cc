# coding: utf-8

# std
import re

# Third_party
from generator.cpp import ast

# App
from generators_cpp_code.v8_api_gen import scalars
import utils_local


class VarDeclaration(object):
    class Type(object):
        def __init__(self, type_name):
            self.name = type_name

    def __init__(self, type_name, name):
        self.type = VarDeclaration.Type(type_name)
        self.name = name


class Holder(object):
    @staticmethod
    def first_filtration(code_lines):
        """ Возвращает строку, в которой содержится все пары тип + имя переменной

        class {
            // Work
            Type var;
            Type function(Type var);
            Type var[SOME];

            Type function(
                Type0 var);

            // Don't work
            Type<Type<
                Var> var;
            Type function(
                Type1 var,
                Type0 var);

            // May be not work
            Type function() {

            }
        }
        """
        result = []
        filter_regex = "bool""|int""|vector<""|string""|char"

        for line in code_lines:
            # Фильтрация кода
            # Может негенерить много ошибок
            # Можно внутри класса разбить так.
            # Сперва вытянуть в строку.
            # Затем разбить ;/:/ и только потом отфильтровать.
            if '(' not in line \
                    and ")" not in line \
                    and ";" in line \
                    and "{" not in line \
                    and "}" not in line \
                    and "#" not in line \
                    and "public:" not in line \
                    and "private" not in line \
                    and "protected" not in line \
                    and "using" not in line:
                pattern = re.compile(filter_regex)
                search_result = pattern.search(line)
                if search_result:
                    line_copy = line
                    line_copy = line_copy.lstrip().rstrip()
                    line_copy = utils_local.remove_cc_comments(line_copy)
                    line_copy = utils_local.delete_double_spaces(line_copy)
                    result.append(line_copy)

        return '\n'.join(result)

    @staticmethod
    def extract_var_declaration(source):
        code_lines = source.split('\n')
        declaration_string = Holder.first_filtration(code_lines)

        # Похоже вся магия здесь
        folded_string = Holder.end_filtration(declaration_string)

        # Похоже на итоговую запаковку
        type_name_list = Holder.make_type_value_list(folded_string)
        return type_name_list

    @staticmethod
    def remove_lr_spaces(string):
        return string.rstrip().lstrip()

    @staticmethod
    def make_type_value_list(folded_string):
        folded_string = Holder.remove_lr_spaces(folded_string)

        intermediate = []
        for at in folded_string.split(';'):
            pair = Holder.remove_lr_spaces(at)
            if not ('*' in pair or '=' in pair or 'const' in pair or 'static' in pair or pair.count('[') > 1):
                intermediate.append(pair)

        declarations = ' '.join(intermediate).split(' ')

        result = []
        var_type = ""
        # Bug was here
        for index, record in enumerate(declarations):
            record = Holder.remove_lr_spaces(record)  # Да, эти лучше тоже отфильтровать
            if record:
                if index % 2:
                    var_name = record
                    if var_type and var_name:
                        result.append((var_type, var_name))
                else:
                    var_type = record
                    # Bug was here
        return result

    @staticmethod
    def end_filtration(declaration_string):
        declaration_string = declaration_string\
            .replace('\t', " ") \
            .replace('\n\t', " ") \
            .replace("  ", " ") \
            .replace('\n', " ")
        declaration_string = utils_local.delete_double_spaces(declaration_string)
        return declaration_string


def extract_variable_declaration(source, header_file_name):
    """
    Abstract:
        Extract variable declaration form C++ header file.
    Args:
        source - content header file
        header_file_name - name header file

    Returns:
        [VarField0, ...]
    """
    result = []
    builder = ast.BuilderFromSource(source, header_file_name)
    try:
        for node in builder.Generate():
            if isinstance(node, ast.Class):
                for record in node.body:
                    if isinstance(record, ast.VariableDeclaration):
                        # модификаторы и... *, & отделены от имени типа!
                        #if scalar?:
                        #elif  vector? std::vector<string>, Vector, List, Array...
                        # это не скаляр и сеттер будет другим https://developers.google.com/v8/embed
                        #else
                        #check what happened
                        result.append(scalars.ScalarVariableField(node.name, record))
        return result
    except KeyboardInterrupt:
        return None
    except Exception as e:
        return None