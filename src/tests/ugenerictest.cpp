#include "../test.h"

#include "ugeneric/ugeneric.h"

static void GenStat(Stat* s, ugeneric_t v) {
    ugeneric_t *array;
    uvector_t *vec;
    size_t vec_size;
    udict_t *d;
    udict_iterator_t *di;

    switch (ugeneric_get_type(v)) {
    case G_DICT_T:
        d = (udict_t *)G_AS_PTR(v);
        di = udict_iterator_create(d);
        while (udict_iterator_has_next(di)) {
            ugeneric_kv_t kv = udict_iterator_get_next(di);
            GenStat(s, kv.v);
            s->stringCount++;
            s->stringLength += strlen(G_AS_STR(kv.k));
            s->memberCount++;
        }
        s->objectCount++;
        udict_iterator_destroy(di);
        break;

    case G_VECTOR_T:
        vec = (uvector_t *)G_AS_PTR(v);
        vec_size = uvector_get_size(vec);
        array = uvector_get_cells(vec);
        for (size_t i = 0; i < vec_size; i++) {
            GenStat(s, array[i]);
            s->elementCount++;
        }
        s->arrayCount++;
        break;

    case G_STR_T:
        s->stringCount++;
        s->stringLength += strlen(G_AS_STR(v));
        break;

    case G_INT_T:
    case G_REAL_T:
        s->numberCount++;
        break;

    case G_BOOL_T:
        if (G_IS_TRUE(v)) {
            s->trueCount++;
        } else {
            s->falseCount++;
        }
        break;

    case G_NULL_T:
        s->nullCount++;
        break;

    default:
        break;
    }
}

class ugenericParseResult : public ParseResultBase {
public:
    ugenericParseResult() : root() {}
    ~ugenericParseResult() { ugeneric_destroy(root, NULL); }

    ugeneric_t root;
};

class ugenericStringResult : public StringResultBase {
public:
    ugenericStringResult() : s() {}
    ~ugenericStringResult() { free(s); }

    virtual const char* c_str() const { return s; }

    char* s;
};

class ugenericTest : public TestBase {
public:
#if TEST_INFO
    virtual const char* GetName() const { return "ugeneric (C)"; }
    virtual const char* GetFilename() const { return __FILE__; }
#endif

#if TEST_PARSE
    virtual ParseResultBase* Parse(const char* json, size_t length) const {
        (void)length;
        ugenericParseResult* pr = new ugenericParseResult;
        pr->root = ugeneric_parse(json);
        if (G_IS_ERROR(pr->root))
        {
            ugeneric_error_destroy(pr->root);
            pr->root.type = G_NULL_T;
            delete pr;
            return 0;
        }
        return pr;
    }
#endif

#if TEST_STRINGIFY
    virtual StringResultBase* Stringify(const ParseResultBase* parseResult) const {
        const ugenericParseResult* pr = static_cast<const ugenericParseResult*>(parseResult);
        ugenericStringResult* sr = new ugenericStringResult;
        sr->s = ugeneric_as_str(pr->root);
        return sr;
    }
#endif

#if TEST_PRETTIFY
    virtual StringResultBase* Prettify(const ParseResultBase* parseResult) const {

        const ugenericParseResult* pr = static_cast<const ugenericParseResult*>(parseResult);
        ugenericStringResult* sr = new ugenericStringResult;
        sr->s = ugeneric_as_str(pr->root);

        return sr;
    }
#endif

#if TEST_STATISTICS
    virtual bool Statistics(const ParseResultBase* parseResult, Stat* stat) const {
        const ugenericParseResult* pr = static_cast<const ugenericParseResult*>(parseResult);
        memset(stat, 0, sizeof(Stat));
        GenStat(stat, pr->root);
        return true;
    }
#endif

#if TEST_CONFORMANCE

    virtual bool ParseDouble(const char* json, double* d) const {
        ugeneric_t r = ugeneric_parse(json);
        if (G_IS_ERROR(r)) {
            ugeneric_error_destroy(r);
            return false;
        }
        if (!G_IS_VECTOR(r)) {
            ugeneric_destroy(r, NULL);
            return false;
        }

        uvector_t *v = (uvector_t *)G_AS_PTR(r);
        ugeneric_t f = uvector_get_at(v, 0);
        *d = G_AS_REAL(f);
        ugeneric_destroy(r, NULL);

        return true;
    }

    virtual bool ParseString(const char* json, std::string& s) const {
        ugeneric_t r = ugeneric_parse(json);
        if (G_IS_ERROR(r)) {
            ugeneric_error_destroy(r);
            return false;
        }
        if (!G_IS_VECTOR(r)) {
            ugeneric_destroy(r, NULL);
            return false;
        }
        uvector_t *v = (uvector_t *)G_AS_PTR(r);
        ugeneric_t str = uvector_get_at(v, 0);
        s = G_AS_STR(str);
        ugeneric_destroy(r, NULL);
        return true;
    }

#endif
};

REGISTER_TEST(ugenericTest);
