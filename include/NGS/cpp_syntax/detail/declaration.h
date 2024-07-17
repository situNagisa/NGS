#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

/// 
/// @param attr[optional] 
/// @param specifier_seq 
/// @param init_declarator_list[optional] @see `NGS_CSYN_DECLARATION_INIT_DECLARATOR_LIST_`
#define NGS_CSYN_DECLARATION_SIMPLE(attr, specifier_seq, init_declarator_list) attr specifier_seq init_declarator_list

// init declarator list

/// 
/// @param declarator @see `NGS_CSYN_DECLARATION_DECLARATOR_`
/// @param initializer[optional] 
#define NGS_CSYN_DECLARATION_INIT_DECLARATOR_LIST_VARIABLE(declarator, initializer) declarator initializer

/// 
/// @param declarator @see `NGS_CSYN_DECLARATION_DECLARATOR_`
/// @param requires_clause 
#define NGS_CSYN_DECLARATION_INIT_DECLARATOR_LIST_FUNCTION(declarator, requires_clause) declarator requires_clause

// declarator

/// 
/// @param identifier 
/// @param attr[optional]
#define NGS_CSYN_DECLARATION_DECLARATOR_ID(identifier, attr) identifier attr

/// 
/// @param identifier 
/// @param attr[optional]
#define NGS_CSYN_DECLARATION_DECLARATOR_PARAMETER_PACK(identifier, attr) ... identifier attr

/// 
/// @param nested_name_specifier[optional] 
/// @param attr[optional] 
/// @param cv[optional] 
/// @param identifier 
#define NGS_CSYN_DECLARATION_DECLARATOR_POINTER(nested_name_specifier, attr, cv, identifier) nested_name_specifier* attr cv identifier

/// 
/// @param attr[optional] 
/// @param declarator 
#define NGS_CSYN_DECLARATION_DECLARATOR_LVALUE_REFERENCE(attr, declarator) & attr declarator

/// 
/// @param attr[optional] 
/// @param declarator 
#define NGS_CSYN_DECLARATION_DECLARATOR_RVALUE_REFERENCE(attr, declarator) && attr declarator

/// 
/// @param noptr_declarator 
/// @param constant_expression 
/// @param attr[optional] 
#define NGS_CSYN_DECLARATION_DECLARATOR_ARRAY(noptr_declarator, constant_expression, attr) noptr_declarator [constant_expression] attr

/// 
/// @param noptr_declarator 
/// @param parameter_list[optional] 
/// @param cv[optional] 
/// @param ref[optional] 
/// @param except[optional] 
/// @param attr[optional] 
#define NGS_CSYN_DECLARATION_DECLARATOR_FUNCTION(noptr_declarator, parameter_list, cv, ref, except, attr) noptr_declarator (parameter_list) cv ref except attr


NGS_LIB_MODULE_END