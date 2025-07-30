#pragma once

namespace src
{
	class Buffer
	{
	public:
		Buffer(void);
		~Buffer(void);

		void SetData(void* data, size_t size);
		void SetData(void* data, size_t size, unsigned int offset);
		void DeleteData(void);

		operator unsigned int(void) const noexcept;
	private:
		unsigned int m_buffer;
	};


}