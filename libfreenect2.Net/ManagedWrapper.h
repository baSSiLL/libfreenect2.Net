#pragma once

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
				_instance = instance;
			}

			!ManagedWrapper()
			{
				if (_instance != nullptr)
				{
					delete _instance;
				}
			}

			property T* Instance
			{
				T* get() { return _instance; }
			}

		public:
			virtual ~ManagedWrapper()
			{
				this->!ManagedWrapper();
			}
		};
	}
}