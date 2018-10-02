package Classes;

public class BaseClass {
    private String name;

    public BaseClass(String n)    { name=n; }
    public BaseClass(BaseClass b) { name=b.name; }
    public String print() { return name; }
    public void setName(String n) { this.name=n; }
    public String getName() { return name; }
}
