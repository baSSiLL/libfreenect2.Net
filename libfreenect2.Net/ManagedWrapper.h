#pragma once

using namespace System;

namespace libfreenect2Net
{
	namespace Internals
	{
		template<class T>
		public ref class ManagedWrapper
		{
		private:
			initonly T* _instance;

		protected:
			ManagedWrapper(T* instance)
			{
				if (instance == nullptr)
					throw gcnew ArgumentNullException("instance");

				_instance = instance;
			}

			!ManagedWrapper()
			{
				delete _instance;
			}

		protected:
			property T* Instance
			{
				T* get() { return _instance; }
			}

		internal:
			static operator T*(ManagedWrapper^ wrapper)
			{
				return wrapper == nullptr ? nullptr : wrapper->Instance;
			}

		public:
			virtual ~ManagedWrapper()
			{
				this->!ManagedWrapper();
			}
		};
	}
}