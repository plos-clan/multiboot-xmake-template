set_project("ExampleOS")

add_rules("mode.debug", "mode.release")
add_requires("zig")

set_arch("i386")
set_optimize("fastest")
set_warnings("all", "extra", "pedantic", "error")

set_policy("run.autobuild", true)
set_policy("check.auto_ignore_flags", false)

target("kernel")
    set_kind("binary")
    set_languages("c23")
    set_toolchains("@zig")
    set_default(false)

    add_includedirs("include")
    add_files("src/**.s", "src/**.c")

    add_ldflags("-nostdlib", "-T", "linker.ld")
    add_cflags("-m32", "-nostdlib", "-flto")
    add_cflags("-mno-80387", "-mno-mmx", "-mno-sse", "-mno-sse2")
    add_asflags("-Wno-unused-command-line-argument")

target("iso")
    set_kind("phony")
    add_deps("kernel")
    set_default(true)

    on_build(function (target)
        import("core.project.project")
        local iso_dir = "$(buildir)/iso_dir"

        if os.exists(iso_dir) then
            os.rmdir(iso_dir)
        end

        os.cp("assets", iso_dir)
        local target = project.target("kernel")
        os.cp(target:targetfile(), iso_dir .. "/kernel.elf")
        local iso_file = "$(buildir)/exampleos.iso"

        -- GRUB Build ISO (commented out)
        -- os.run("grub-mkrescue -o %s %s", iso_file, iso_dir)

        -- Limine Build ISO
        local xorriso_flags = "-b limine/limine-bios-cd.bin -no-emul-boot -boot-info-table"
        os.run("xorriso -as mkisofs %s %s -o %s", xorriso_flags, iso_dir, iso_file)

        print("ISO image created at: " .. iso_file)
    end)

    on_run(function (target)
        import("core.project.config")

        local flags = {
            "-M", "q35",
            "-serial", "stdio",
            "-cdrom", config.buildir() .. "/exampleos.iso"
        }
        
        os.runv("qemu-system-x86_64", flags)
    end)
