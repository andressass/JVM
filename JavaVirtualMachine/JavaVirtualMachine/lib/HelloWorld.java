import entidades.Aluno;
import entidades.Matematica;
import entidades.Calc;

public class HelloWorld {
    
    
    
    static int int1 = 22;
    static  int int2 = 12;
    static  int int3 = -12;
    static double a = 38.0;
    static double b = -12.0;
    static long l1 = 3000;
    static long l2 = -3000;
    static String s = "TESTES";
    static long l3 = 5050;


    public static void main(String[] args) {
//        // Prints "Hello, World" to the terminal window.
//        
//        int[][][][] string = {
//            {
//                {
//                    {3,4},
//                    {3,4}
//                },
//                {
//                    {
//                        3,4
//                    },
//                    {
//                        3,4
//                    }
//                }
//            },
//            
//            {
//                {{3,4},{3,4}},
//                {{3,4},{3,4}}
//            }
//        };
//
//        System.out.println("Nome do aluno  : " + string[0][0][0][0]);
        
//         String array[] = {"VACA","CACHORRO","PERIQUITO","PSKRANIA"};
//
//        System.out.println("Valor do array : " + array[0]);
//        System.out.println("Valor do array : " + array[1]);
//        System.out.println("Valor do array : " + array[2]);
//        System.out.println("Valor do array : " + array[3]);
        
        int int4 = 12;
        int int5 = -3;
        double c = 98.0;
        double d = -152.0;

        
        System.out.println(l1);
        System.out.println(l2);
        System.out.println(int2);
        System.out.println(a);
        System.out.println(b);
        System.out.println(s);
        
        
        Aluno aluno = new Aluno(8);
        
        aluno.setIdade(53.32);
        aluno.setNome("Rondinele");
        
        System.out.println("Nome do aluno  : " + aluno.getNome());
        System.out.println("Idade do aluno : " + aluno.getIdade());
        System.out.println("Idade verdadeira do aluno : " + aluno.getIdadeVerdadeira());
        System.out.println("Matricula : " + aluno.getMatricula());
        System.out.println("Serie : " + aluno.serie);


        Matematica m;
        
        m= new Calc();
        
        System.out.println("Soma : " + m.soma(2,3));
        System.out.println("PI : " + m.pi);
        
    }
}
