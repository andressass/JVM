import entidades.Aluno;
import entidades.Matematica;
import entidades.Calc;

public class HelloWorld {
    
    static int[][] create3DArray() {
        int grid[][];
        grid = new int[10][5];
        return grid;
    }

    public static void main(String[] args) {
        
        int grid[][] = create3DArray();
        
        grid[0][0] = 125;
        
        System.out.println("Nome do aluno  : " + grid[0][0]);
        
//        // Prints "Hello, World" to the terminal window.
        
//        int[][][][] string = {
//            {
//                {{3,4},{3,4}},
//                {{3,4},{3,4}}},
//            {
//                {{3,4},{3,4}},
//                {{3,4},{3,4}}
//            }
//        };
//
//        System.out.println("Nome do aluno  : " + string[0][0][0][0]);
        
        
//        Aluno aluno = new Aluno(8);
//        
//        aluno.setIdade(53.32);
//        aluno.setNome("Rondinele");
//        
//        System.out.println("Nome do aluno  : " + aluno.getNome());
//        System.out.println("Idade do aluno : " + aluno.getIdade());
//        System.out.println("Idade verdadeira do aluno : " + aluno.getIdadeVerdadeira());
//        System.out.println("Matricula : " + aluno.getMatricula());
//        System.out.println("Serie : " + aluno.serie);
//        
//
//        Matematica m;
//        
//        m= new Calc();
//        
//        System.out.println("Soma : " + m.soma(2,3));
//        System.out.println("PI : " + m.pi);
     
    }
}
