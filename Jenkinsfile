pipeline {
    agent any
    stages {
        stage('[ETHAN] Cleanup') {
            steps {
                sh "rm -rf bin"
                sh "rm -rf lib"
                sh "rm -rf build"
                sh "rm -rf compile_command.json"
                sh "git submodule update --init --recursive"
            }
        }
        stage('[ETHAN] CMake Build') {
            steps {
                cmakeBuild buildType: 'Debug', cleanBuild: true, generator: 'Unix Makefiles', buildDir: 'build', installation: 'InSearchPath', steps: [[withCmake: true]]
            }
        }
        stage('Run') {
            steps {
                sh "./bin/GAME"
            }
        }
    }
}
