#ifndef expression_hpp
#define expression_hpp

#include "runtime_context.hpp"
#include "compiler_context.hpp"
#include "tokenizer.hpp"

#include <string>

namespace stork {
	template <typename R>
	class expression {
		expression(const expression&) = delete;
		void operator=(const expression&) = delete;
	protected:
		expression() = default;
	public:
		using ptr = std::unique_ptr<const expression>;
		
		virtual R evaluate(runtime_context& context) const = 0;
		virtual ~expression() = default;
	};
	
	struct function_argument {
		lvalue value;
		
		function_argument(lvalue value);
		function_argument(number n);
		function_argument(string str);
	};
	
	using retval = function_argument;
	
	expression<void>::ptr build_empty_expression();
	expression<void>::ptr build_void_expression(compiler_context& context, tokens_iterator& it);
	expression<number>::ptr build_number_expression(compiler_context& context, tokens_iterator& it);
	expression<retval>::ptr build_retval_expression(compiler_context& context, tokens_iterator& it, type_handle type_id);
}

#endif /* expression_hpp */
