#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
#include "ffms.h"

namespace nodeffms2 {
    using namespace v8;
    using namespace node;

    struct OpenRequest {
        char* filepath;
        Persistent<Promise::Resolver> promise;
    };

    class NodeFFMS2 : public ObjectWrap {
        public:
            static void Init(Local<Object> exports, Local<Object> module) {
                FFMS_Init(0, 0);

                Isolate* isolate = exports->GetIsolate();
                Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
                tpl->SetClassName(String::NewFromUtf8(isolate, "FFMS2"));
                tpl->InstanceTemplate()->SetInternalFieldCount(1);

                // prototypes
                NODE_SET_PROTOTYPE_METHOD(tpl, "open", Open);
                NODE_SET_PROTOTYPE_METHOD(tpl, "metadata", MetaData);

                constructor.Reset(isolate, tpl->GetFunction());
                module->Set(String::NewFromUtf8(isolate, "exports"), tpl->GetFunction());
            }

        private:
            static Persistent<Function> constructor;

            // char* sourceFile;
            FFMS_Indexer* indexer;
            FFMS_Index* index;
            FFMS_ErrorInfo errInfo;
            FFMS_VideoSource *videoSource;

            static void New(const FunctionCallbackInfo<Value> &args) {
                Isolate* isolate = args.GetIsolate();

                NodeFFMS2* self = new NodeFFMS2();
                self->Wrap(args.This());
                args.GetReturnValue().Set(args.This());
            }

            static void Open(const FunctionCallbackInfo<Value> &args) {
                NodeFFMS2* self = ObjectWrap::Unwrap<NodeFFMS2>(args.Holder());

                String::Utf8Value v8SourceFile(args[0]);
                char* sourceFile = *v8SourceFile;

                // OpenRequest* reqData = new OpenRequest();
                // reqData->promise = Persistent<Promise::Resolver>::New(isolate);
                // reqData->filepath =* v8SourceFile;

                // uv_work_t* req = new uc_work_t();
                // req->data = reqData;
                // uv_queue_work(uv_default_roop(), req, _OpenAsync)

                char errMessage[1024];
                self->errInfo.Buffer = errMessage;
                self->errInfo.BufferSize = sizeof(errMessage);
                self->errInfo.ErrorType = FFMS_ERROR_SUCCESS;
                self->errInfo.SubType = FFMS_ERROR_SUCCESS;

                self->indexer = FFMS_CreateIndexer(sourceFile, &self->errInfo);
                self->index = FFMS_DoIndexing2(self->indexer, FFMS_IEH_ABORT, &self->errInfo);

                int trackno = FFMS_GetFirstTrackOfType(self->index, FFMS_TYPE_VIDEO, &self->errInfo);
                self->videoSource = FFMS_CreateVideoSource(sourceFile, trackno, self->index, 1, FFMS_SEEK_NORMAL, &self->errInfo);
                FFMS_DestroyIndex(self->index);
            }

            // static

            static void MetaData(const FunctionCallbackInfo<Value> &args) {
                Isolate* isolate = args.GetIsolate();
                Local<Context> context = isolate->GetCurrentContext();
                NodeFFMS2* self = node::ObjectWrap::Unwrap<NodeFFMS2>(args.Holder());

                Local<Promise::Resolver> promise = Promise::Resolver::New(isolate);
                args.GetReturnValue().Set(promise->GetPromise());

                const FFMS_VideoProperties *videoprops = FFMS_GetVideoProperties(self->videoSource);
                // videoprops->Frame

                const Local<Object> metadata = Object::New(isolate);
                metadata->Set(String::NewFromUtf8(isolate, "framerate"), Number::New(isolate, videoprops->FPSDenominator));
                promise->Resolve(context, metadata);
            }
    };

    Persistent<Function> NodeFFMS2::constructor;

    NODE_MODULE(nodeffms2, NodeFFMS2::Init);
}