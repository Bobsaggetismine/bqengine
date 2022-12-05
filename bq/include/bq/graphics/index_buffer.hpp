#pragma once

#include "core.hpp"

namespace bq {

	class BQ_API index_buffer {

		unsigned int m_id;
		unsigned m_count;
		
	public:
		const unsigned* m_data;

		index_buffer(const unsigned* data, unsigned count);
		~index_buffer();
		void bind() const;
		void unbind() const;
		
		inline unsigned count() const { return m_count; }
	};
}