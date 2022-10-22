// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/05/2022
// Updated : 21/10/2022

#ifndef __AK_KILA_COMPILER_CONTEXT__
#define __AK_KILA_COMPILER_CONTEXT__

#include <Akpch.h>

#include "types.h"

#include <Core/core.h>

namespace Ak::Kl
{
	enum class identifier_scope
	{
		global_variable,
		local_variable,
		function
	};

	class identifier_info
	{
		public:
			identifier_info(type_handle type_id, size_t index, identifier_scope scope) : _type_id(type_id), _index(index), _scope(scope) {}

			inline type_handle type_id() const noexcept { return _type_id; }
			inline size_t index() const noexcept { return _index; }
			inline identifier_scope get_scope() const { return _scope; }

		private:
			type_handle _type_id;
			size_t _index;
			identifier_scope _scope;
	};

	class identifier_lookup
	{
		public:
			inline virtual const identifier_info* find(const std::string& name) const
			{
				auto it = _identifiers.find(name);
				return it != _identifiers.end() ? &it->second : nullptr;
			}
			virtual const identifier_info* create_identifier(std::string name, type_handle type_id) = 0;
			inline bool can_declare(const std::string& name) const
			{
				return _identifiers.find(name) == _identifiers.end();
			}

			virtual ~identifier_lookup() = default;

		protected:
			inline const identifier_info* insert_identifier(std::string name, type_handle type_id, size_t index, identifier_scope scope)
			{
				return &_identifiers.emplace(std::move(name), identifier_info(type_id, index, scope)).first->second;
			}
			inline size_t identifiers_size() const noexcept { return _identifiers.size(); }

		private:
			std::unordered_map<std::string, identifier_info> _identifiers;
	};

	class global_variable_lookup: public identifier_lookup
	{
		public:
			inline const identifier_info* create_identifier(std::string name, type_handle type_id) override
			{
				return insert_identifier(std::move(name), type_id, identifiers_size(), identifier_scope::global_variable);
			}
	};

	class local_variable_lookup: public identifier_lookup
	{
		public:
			local_variable_lookup(Unique_ptr<local_variable_lookup> parent_lookup) : _parent(std::move(parent_lookup)), _next_identifier_index(_parent ? _parent->_next_identifier_index : 1) {}
			inline const identifier_info* find(const std::string& name) const override
			{
				if(const identifier_info* ret = identifier_lookup::find(name))
					return ret;
				return _parent ? _parent->find(name) : nullptr;
			}
			inline const identifier_info* create_identifier(std::string name, type_handle type_id) override
			{
				return insert_identifier(std::move(name), type_id, _next_identifier_index++, identifier_scope::local_variable);
			}
			inline Unique_ptr<local_variable_lookup> detach_parent() { return std::move(_parent); }

		private:
			Unique_ptr<local_variable_lookup> _parent;
			int _next_identifier_index;
	};

	class param_lookup: public local_variable_lookup
	{
		public:
			param_lookup() : local_variable_lookup(nullptr), _next_param_index(-1) {}
			inline const identifier_info* create_param(std::string name, type_handle type_id)
			{
				return insert_identifier(std::move(name), type_id, _next_param_index--, identifier_scope::local_variable);
			}

		private:
			int _next_param_index;
	};

	class function_lookup: public identifier_lookup
	{
		public:
			inline const identifier_info* create_identifier(std::string name, type_handle type_id) override
			{
				return insert_identifier(std::move(name), type_id, identifiers_size(), identifier_scope::function);
			}
	};

	class compiler_context
	{
		class scope_raii
		{
			public:
				scope_raii(compiler_context& context) : _context(context) { _context.enter_scope(); }
				~scope_raii() { _context.leave_scope(); }

			private:
				compiler_context& _context;
		};

		class function_raii
		{
			public:
				function_raii(compiler_context& context) : _context(context) { _context.enter_function(); }
				~function_raii() { _context.leave_scope(); }

			private:
				compiler_context& _context;
		};

		public:
			compiler_context() : _params(nullptr) {}
			inline type_handle get_handle(const type& t) { return _types.get_handle(t); }
			const identifier_info* find(const std::string& name) const;
		
			inline const identifier_info* create_identifier(std::string name, type_handle type_id)
			{
				return _locals ? _locals->create_identifier(std::move(name), type_id) : _globals.create_identifier(std::move(name), type_id);
			}
			inline bool can_declare(const std::string& name) const
			{
				return _locals ? _locals->can_declare(name) : (_globals.can_declare(name) && _functions.can_declare(name));
			}
			
			inline const identifier_info* create_param(std::string name, type_handle type_id)    { return _params->create_param(name, type_id); }
			inline const identifier_info* create_function(std::string name, type_handle type_id) { return _functions.create_identifier(name, type_id); }
			inline scope_raii scope() { return scope_raii(*this); }
			inline function_raii function() { return function_raii(*this); }

		private:
			function_lookup _functions;
			global_variable_lookup _globals;
			param_lookup* _params;
			Unique_ptr<local_variable_lookup> _locals;
			type_registry _types;

			inline void enter_function()
			{
				Unique_ptr<param_lookup> params = create_Unique_ptr<param_lookup>();
				_params = params.get();
				_locals.reset(params.get());
			}
			inline void enter_scope()
			{
				_locals = create_Unique_ptr<local_variable_lookup>(std::move(_locals));
			}
			void leave_scope();
	};
}

#endif // __AK_KILA_COMPILER_CONTEXT__
