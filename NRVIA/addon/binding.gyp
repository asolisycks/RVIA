{
    "targets": [
        {
            "target_name": "adnrvia",
            "sources": [ "adrvia.cpp", "CRvia.cpp" ],
            "conditions": [
                ["OS=='win'", {
                    "msvs_settings": {
                        "VCCLCompilerTool": {
                            "AdditionalOptions": [ "/std:c++20" ]
                        }
                    }
                }],
                ["OS=='linux'", {
                    "cflags": [ "-std=c++20" ],
                    "cflags_cc": [ "-std=c++20" ]
                }]
            ]
        }
    ]
}
