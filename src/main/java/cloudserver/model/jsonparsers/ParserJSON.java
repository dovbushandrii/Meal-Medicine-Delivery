package cloudserver.model.jsonparsers;

public interface ParserJSON {
    Object parse(String json, Class clazz);
}
