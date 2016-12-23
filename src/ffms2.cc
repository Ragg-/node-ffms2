#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include "../deps/ffms2/include/ffms.h"

namespace nodeffms2 {
    using namespace v8;

    class NodeFFMS2 : public node::ObjectWrap {
        public:
            static void Init(Local<Object> exports) {

            }

        private:
            static Persistent<Function> constructor;

            static void New(const FunctionCallbackInfo<Value> &args) {
                Isolate *isolate = args.GetIsolate();
                NodeFFMS2 *self = new NodeFFMS2();
                self->Wrap(args.This());
                args.GetReturnValue().Set(args.This());
            }
    };

    Persistent<Function> NodeFFMS2::constructor;

    NODE_MODULE(nodeffms2, NodeFFMS2::Init);
}