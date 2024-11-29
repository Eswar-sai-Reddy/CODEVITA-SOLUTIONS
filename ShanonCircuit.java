import java.util.*;

public class ShannonCircuits {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        int n = Integer.parseInt(s.nextLine());
        Map<String, String[]> g = new HashMap<>();

        for (int i = 0; i < n; i++) {
            String[] p = s.nextLine().split("=");
            String k = p[0].trim();
            String[] d = p[1].trim().split("[(), ]+");
            g.put(k, d);
        }

        int t = Integer.parseInt(s.nextLine());
        Map<String, int[]> v = new HashMap<>();

        while (true) {
            String l = s.nextLine();
            if (l.matches("[a-zA-Z]+")) {
                f(g, v, l.trim(), t);
                break;
            }

            String[] p = l.split(" ");
            String k = p[0];
            int[] arr = Arrays.stream(p, 1, p.length).mapToInt(Integer::parseInt).toArray();
            v.put(k, arr);
        }
    }

    private static void f(Map<String, String[]> g, Map<String, int[]> v, String t, int c) {
        Map<String, int[]> o = new HashMap<>();
        for (String k : g.keySet()) {
            o.put(k, new int[c]);
        }

        for (int i = 1; i < c; i++) {
            for (String k : g.keySet()) {
                String[] d = g.get(k);
                String op = d[0], x = d[1], y = d[2];
                int a = g(x, o, v, i - 1);
                int b = g(y, o, v, i - 1);
                o.get(k)[i] = c(op, a, b);
            }
        }

        int[] r = o.get(t);
        for (int i = 0; i < c; i++) {
            System.out.print(r[i] + (i == c - 1 ? "" : " "));
        }
    }

    private static int g(String x, Map<String, int[]> o, Map<String, int[]> v, int c) {
        return v.containsKey(x) ? v.get(x)[c] : o.get(x)[c];
    }

    private static int c(String op, int x, int y) {
        switch (op) {
            case "AND": return x & y;
            case "OR": return x | y;
            case "NAND": return ~(x & y) & 1;
            case "NOR": return ~(x | y) & 1;
            case "XOR": return x ^ y;
            default: return 0;
        }
    }
}
