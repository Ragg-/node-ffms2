#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include "../deps/ffms2/include/ffms.h"

namespace nodeffms2 {
    using namespace v8;

    class NodeFFMS2 : public node::ObjectWrap {
        public:
            static void Init(Local<Object> exports, Local<Object> module) {
                Isolate *isolate = exports->GetIsolate();
                Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
                tpl->SetClassName(String::NewFromUtf8(isolate, "FFMS2"));
                tpl->InstanceTemplate()->SetInternalFieldCount(1);

                // prototypes
                NODE_SET_PROTOTYPE_METHOD(tpl, "metadata", MetaData);

                constructor.Reset(isolate, tpl->GetFunction());
                module->Set(String::NewFromUtf8(isolate, "exports"), tpl->GetFunction());
            }

        private:
            static Persistent<Function> constructor;

            static void New(const FunctionCallbackInfo<Value> &args) {
                Isolate *isolate = args.GetIsolate();

                NodeFFMS2 *self = new NodeFFMS2();
                self->Wrap(args.This());
                args.GetReturnValue().Set(args.This());
            }

            static void MetaData(const FunctionCallbackInfo<Value> &args) {
                Isolate *isolate = args.GetIsolate();

                Local<Context> context = isolate->GetCurrentContext();
                Local<Promise::Resolver> promise = Promise::Resolver::New(isolate);
                args.GetReturnValue().Set(promise->GetPromise());
                promise->Resolve(context, String::NewFromUtf8(isolate, "hi"));
            }
    };

    Persistent<Function> NodeFFMS2::constructor;

    NODE_MODULE(nodeffms2, NodeFFMS2::Init);
}