#pragma once

namespace Zengine
{
	namespace Utilities
	{
		// Gives you a default of 32 bits.
		template <typename T = int>
		class BitMask
		{
		public:
			BitMask();

		public:
			bool GetBit(const int& aBit) const;
			void SetBit(const int& aBit, const bool& aState);

		private:
			const int myCapacity = -1;
			T myBits = 0;
		};

		template<typename T>
		inline BitMask<T>::BitMask() : myCapacity(sizeof(T) * 8)
		{}

		template<typename T>
		inline bool BitMask<T>::GetBit(const int& aBit) const
		{
			return myBits & (1UL << aBit);
		}

		template<typename T>
		inline void BitMask<T>::SetBit(const int& aBit, const bool& aState)
		{
			if (aBit >= myCapacity) static_assert("Bit to high.");

			if (aState)
			{
				myBits |= (1UL << aBit);
			}
			else
			{
				myBits &= ~(1UL << aBit);
			}
		}
	}

	namespace Util = Utilities;

}

