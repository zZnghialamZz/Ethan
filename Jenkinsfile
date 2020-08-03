pipeline {
    agent any
    options {
        buildDiscarder(logRotator(numToKeepStr: '10', artifactNumToKeepStr: '10'))
    }
    parameters {
        booleanParam name: 'RUN_TESTS', defaultValue: false, description: 'Run Tests?'
        booleanParam name: 'RUN_ANALYSIS', defaultValue: false, description: 'Run Static Code Analysis?'
        booleanParam name: 'DEPLOY', defaultValue: false, description: 'Deploy Artifacts?'
    }
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
    }

    stage('Test') {
        when {
            environment name: 'RUN_TESTS', value: 'true'
        }
        steps {
        }
    }

    stage('Analyse') {
        when {
            environment name: 'RUN_ANALYSIS', value: 'true'
        }
        steps {
            // sh label: '', returnStatus: true, script: 'cppcheck . --xml --language=c++ --suppressions-list=suppressions.txt 2> cppcheck-result.xml'
            // publishCppcheck allowNoReport: true, ignoreBlankFiles: true, pattern: '**/cppcheck-result.xml'
        }
    }

    stage('Deploy') {
        when {
            environment name: 'DEPLOY', value: 'true'
        }
        steps {
            // sh label: '', returnStatus: true, script: '''cp jenkinsexample ~ cp test/testPro ~'''
        }
    }
}
