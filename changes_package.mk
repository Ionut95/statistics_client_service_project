

BOARD_SEPOLICY_DIRS += device/arpi_customization/sepolicy \
                       device/arpi_customization/sepolicy/statistics_service
                        

PRODUCT_PACKAGES += statistics_service \
                    statistics.service.statisticsservicemanager \
                    StatisticsClientApp

DEVICE_MANIFEST_FILE += device/arpi_customization/manifests/manifest.xml

DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE += device/arpi_customization/manifests/framework_compatibility_matrix.xml


