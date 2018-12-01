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
			bool _detached;
			bool _disposed;

		protected:
			ManagedWrapper(T* instance)
			{
				if (instance == nullptr)
					throw gcnew ArgumentNullException("instance");

				_instance = instance;
				_detached = false;
				_disposed = false;
			}

			!ManagedWrapper()
			{
				if (!_disposed)
				{
					if (!_detached)
					{
						delete _instance;
						Detach();
					}
					_disposed = true;
				}
			}

			property T* Instance
			{
				T* get() 
				{ 
					if (_detached)
						throw gcnew InvalidOperationException("This wrapper is detached.");

					return _instance; 
				}
			}

		internal:
			static operator T*(ManagedWrapper^ wrapper)
			{
				return Object::ReferenceEquals(wrapper, nullptr) ? nullptr : wrapper->Instance;
			}

			/// <summary>Detaches this wrapper from underlying managed instance.</summary>
			/// <remarks>
			/// When detached
			/// * <see cref="Instance"/> property cannot be accessed anymore;
			/// * underlying unmanaged instance is not deleted automatically when this object is disposed/finalized.
			/// This action is irreversible.
			/// </remarks>
			void Detach()
			{
				_detached = true;
			}

		public:
			virtual ~ManagedWrapper()
			{
				this->!ManagedWrapper();
			}

			property bool IsDisposed
			{
				bool get() { return _disposed; }
			}
		};
	}
}