pipeline {
    agent any
    stages {
        stage('[ETHAN] Cleanup Previous Build') {
            steps {
                sh "rm -rf bin"
                sh "rm -rf lib"
                sh "rm -rf build"
                sh "rm -rf compile_command.json"
            }
        }
        stage('[ETHAN] Generate CMake Build Files') {
            steps {
                sh "cmake -H. -B build"
                sh "ln -s build/compile_commands.json ."
            }
        }
        stage('[ETHAN] Compile & Link') {
            steps {
                sh "cmake --build build"
            }
        }
        stage('Run') {
            steps {
                sh "./bin/GAME"
            }
        }
    }
}
