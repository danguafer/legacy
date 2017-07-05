#ifndef SILEXARS_UTILS_AUTOMANAGER_H_
#define SILEXARS_UTILS_AUTOMANAGER_H_

namespace Silexars {
    namespace Utils {
        template <class T, bool isArray = false>
        class AutoManager {
            public:
                AutoManager() { isManaging = false; }
                ~AutoManager() { if (isManaging) delete ptr; }

                void operator=(T* ptr) {
                    if (this->isManaging) delete this->ptr;
                    this->ptr = ptr;
                    this->isManaging = false;
                }

                void manage(T* ptr) {
                    if (this->isManaging) delete this->ptr;
                    this->ptr = ptr;
                    this->isManaging = true;
                }

                operator bool() const { return ptr; }
                operator T*() const { return ptr; }
                T* operator->() const { return ptr; }
            private:
                T* ptr;
                bool isManaging;

        };
        /*
        template <class T>
        class AutoManager<T,true> {
            public:
                T ptr;
                bool isManaging;

                AutoManager() { isManaging = false; }
                AutoManager(T ptr, bool isManaging) {
                    this->ptr = ptr;
                    this->isManaging = isManaging;
                }
                ~AutoManager() { if (isManaging) delete[] ptr; }

                void assign(T ptr, bool isManaging) {
                    if (this->isManaging) delete[] this->ptr;
                    this->ptr = ptr;
                    this->isManaging = isManaging;
                }

                void operator=(T ptr) { assign(ptr,false); }

                operator bool() { return ptr; }
                operator T() { return ptr; }
                T* operator->() { return ptr; }
        };
        */
    }
}

#endif // SILEXARS_UTILS_AUTOMANAGER_H_
