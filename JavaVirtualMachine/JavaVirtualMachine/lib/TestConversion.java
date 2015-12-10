
public class TestConversion {
  public static void main(String[] args) {
    int ia = 1,ib = 1;
    long la = 1,lb = 1;
    double da = 1, db = 1;
    float fa = 1, fb = 1;
    char ca = 1, cb = 1;
    byte ba = 1, bb = 1;
    short sa = 1, sb = 1;

    ib = (int) la;
    fb = (float) la;
    db = (double)la;

    System.out.println("\n======= Longs");
    System.out.println("Int: "+ib);
    System.out.println("Float: "+fb);
    System.out.println("Double: "+db);

    lb = (long) ia;
    fb = (float)ia;
    db = (double)ia;

    System.out.println("======= Ints");
    System.out.println("Long: "+lb);
    System.out.println("Double: "+db);
    System.out.println("Float: "+fb);

    ib = (int) fa;
    lb = (long) fa;
    db = (double)fa;

    System.out.println("\n======= Floats");
    System.out.println("Int: "+ib);
    System.out.println("Long: "+lb);
    System.out.println("Double: "+db);

    ib = (int) da;
    lb = (long) da;
    fb = (float)da;

    System.out.println("\n======= Doubles");
    System.out.println("Int: "+ib);
    System.out.println("Long: "+lb);
    System.out.println("Float: "+fb);

    bb = (byte) ia;
    cb = (char) ia;
    sb = (short) ia;

    System.out.println("\n======= 2 Ints");
    System.out.println(bb);
    System.out.println(cb);
    System.out.println(sb);
  }
}
