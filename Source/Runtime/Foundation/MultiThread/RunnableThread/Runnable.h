#pragma once
#include "../../Foundation.h"

namespace mikasa::Runtime::Foundation
{
    class RunnableThread;

    /**
     * represents the logic run on a thread.
     */
    class Runnable
    {
    public:
        Runnable() = default;
        virtual ~Runnable() = default;

    public:
        /**
         * run on created thread.
         * if Init fail, thread creator will destroy the thread.
         * @return success or fail.
         */
        virtual bool Init() = 0;

        /**
         * run on created thread.
         * main logic of this runnable.
         * @return
         */
        virtual uint32 Run() = 0;

        /**
         * run on created thread.
         * called after Run return.
         */
        virtual void Exit() = 0;


        /**
         * run on caller thread when attached thread is killed.
         */
        virtual void Stop() = 0;


        void BindThread(RunnableThread* thread)
        {
            MIKASA_ASSERT(Thread_ == nullptr);
            Thread_ = thread;
        }

        RunnableThread* GetThread()
        {
            return Thread_;
        }

    protected:
        RunnableThread* Thread_ = nullptr;
    };
}

