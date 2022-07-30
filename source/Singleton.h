#pragma once
namespace Elite
{
    template <typename T>
    class Singleton
    {
    public:
        static T& GetInstance()
        {
            static T instance;
            return instance;
        }

        virtual ~Singleton() = default;
    protected:
        Singleton() = default;

        Singleton(const Singleton& other) = delete;

        Singleton(Singleton&& other) = delete;
        
        Singleton& operator=(const Singleton& other) = delete;

        Singleton& operator=(Singleton&& other) = delete;
    };
}