pipeline {
    agent { label 'docker' }

    stages {
        stage('mborne/graph-experiments:latest') {
            steps {
                script {
                    def build_args = "--pull --no-cache ";

                    def customImage = docker.build('mborne/graph-experiments:latest'," ${build_args} .")
                    customImage.inside {
                        sh 'build/test/egraph-test --log_format=JUNIT --log_sink=junit.xml --log_level=all --report_level=no'

                        /* publish reports */
                        junit 'junit.xml'
                    }

                    // docker.withRegistry("${DOCKER_REGISTRY_URL}","${DOCKER_REGISTRY_CREDENTIAL_ID}") {
                    //     customImage.push("latest")
                    // }
                }
            }
        }
    }

}
